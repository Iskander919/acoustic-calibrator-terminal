#include "mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * @return none
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {


    setupUi();
    setupConnections();

    serial = new QSerialPort();

    updatePortsList();

}

/**
 * @brief MainWindow::setupUi: function that setups layouts and ui elements
 * @param none
 * @return none
 */
void MainWindow::setupUi() {

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    mainLayout = new QHBoxLayout(central);

    setupButtonLayout();
    setupConsoleLayout();

    mainLayout -> addLayout(buttonLayout);
    mainLayout -> addLayout(consoleLayout);

}

/**
 * @brief MainWindow::setupConnections
 * @param none
 * @return none
 */
void MainWindow::setupConnections() {

    // connecting Close button
    connect(closeButton, &QPushButton::clicked, this, &MainWindow::closeClicked);


    /*
    // connecting timer timeout for updating available ports:
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePortsList);
    */

    // connecting Connect button
    connect(setConnectionButton, &QPushButton::clicked, this, &MainWindow::connectClicked);

    // connecting switcher to 94 dB
    connect(setModeButton94, &QPushButton::clicked, this, &MainWindow::switchClicked94);

    // connecting switcher to 114 dB
    connect(setModeButton114, &QPushButton::clicked, this, &MainWindow::switchClicked114);

    // connecting Send button
    connect(setCoeffsButton, &QPushButton::clicked, this, &MainWindow::sendDataClicked);
}

/**
 * @brief MainWindow::setupButtonLayout
 * @param none
 * @return none
 */
void MainWindow::setupButtonLayout() {

    buttonLayout = new QVBoxLayout();

    // implememnting buttons of main window:
    setConnectionButton = new QPushButton(CONNECT_BUTTON_LABEL);
    setModeButton94     = new QPushButton(SWITCH_TO_94_BTN_LABEL);
    setModeButton114    = new QPushButton(SWITCH_TO_114_BTN_LABEL);
    setCoeffsButton     = new QPushButton(SET_COEFFS_BUTTON_LABEL);
    writeMemoryButton   = new QPushButton(WRITE_MEM_BUTTON_LABEL);
    eraseMemoryButton   = new QPushButton(ERASE_MEM_BUTTON_LABEL);
    closeButton         = new QPushButton(CLOSE_BUTTON_LABEL);

    // implementing drop-down menu for COM-port selection
    comPortSelector = new QComboBox();
    buttonLayout -> addWidget(comPortSelector);

    // implementing drop-down menu for mode selection
    modeSelector = new QComboBox();
    modeSelector -> addItem(MODE_94_LABEL);
    modeSelector -> addItem(MODE_114_LABEL);
    buttonLayout -> addWidget(modeSelector);

    // adding buttons to layout:
    buttonLayout -> addWidget(setConnectionButton);
    buttonLayout -> addWidget(setModeButton94);
    buttonLayout -> addWidget(setModeButton114);
    buttonLayout -> addWidget(setCoeffsButton);
    buttonLayout -> addWidget(writeMemoryButton);
    buttonLayout -> addWidget(eraseMemoryButton);
    buttonLayout -> addWidget(closeButton);

    setCoeffsButton   -> setEnabled(false);
    writeMemoryButton -> setEnabled(false);
    eraseMemoryButton -> setEnabled(false);
    setModeButton94   -> setEnabled(false);
    setModeButton114  -> setEnabled(false);

}

/**
 * @brief MainWindow::setupConsoleLayout
 * @param parentWidget
 * @return none
 */
void MainWindow::setupConsoleLayout() {

    consoleLayout = new QVBoxLayout();

    console = new QPlainTextEdit();

    // setting font for console(QPlaintextEdit);
    QFont consoleFont(CONSOLE_FONT, CONSOLE_FONT_SIZE);
    consoleFont.setStyleHint(QFont::Monospace);
    console -> setFont(consoleFont);

    console -> setReadOnly(true);

    correctionEdit = new QLineEdit();
    pCoeffEdit     = new QLineEdit();
    iCoeffEdit     = new QLineEdit();
    dCoeffEdit     = new QLineEdit();

    // defining labels for line edits
    QLabel *correctionEditLabel = new QLabel(CORRECTION_EDIT_LABEL);
    QLabel *pEditLabel = new QLabel(P_EDIT_LABEL);
    QLabel *iEditLabel = new QLabel(I_EDIT_LABEL);
    QLabel *dEditLabel = new QLabel(D_EDIT_LABEL);

    // adding widgets to console layout
    consoleLayout -> addWidget(correctionEditLabel);
    consoleLayout -> addWidget(correctionEdit);

    consoleLayout -> addWidget(pEditLabel);
    consoleLayout -> addWidget(pCoeffEdit);

    consoleLayout -> addWidget(iEditLabel);
    consoleLayout -> addWidget(iCoeffEdit);

    consoleLayout -> addWidget(dEditLabel);
    consoleLayout -> addWidget(dCoeffEdit);

    // adding console
    consoleLayout -> addWidget(console);

}

/**
 * @brief MainWindow::updatePortsList
 */
void MainWindow::updatePortsList() {

    // adding available COM ports to COM port selector

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {

        comPortSelector -> addItem(info.portName());

    }

}

/**
 * @brief MainWindow::connectClicked
 * @param none
 * @return none
 */
void MainWindow::connectClicked() {

    serialDriver = new SerialDriver;

    // getting COM Port number from comPortSelector(ComboBox) and opening it
    serialDriver -> openSerialPort(this -> comPortSelector -> currentText());

    // writing message to console:
    if (serialDriver -> openedSuccesfully()) {

        console -> appendPlainText(CONNECTION_SUCCESS_LABEL + (this -> comPortSelector -> currentText()));

        // enbaling buttons after successful connection
        setCoeffsButton   -> setEnabled(true);
        setModeButton94   -> setEnabled(true);
        setModeButton114  -> setEnabled(true);

    }

    //debug----------------------------------------------------------------------//
    std::array<uint8_t, 20> combined = serialDriver -> combineArray(0.00001, 0.0000015, 0.00001, 0.000245, 3500);
    for(int i = 0; i < 20; i++) {

        std::cout << std::hex << std::setw(3) << static_cast<int>(combined[i]);

    }

    std::cout << std::endl;

    //---------------------------------------------------------------------------//

}

/**
 * @brief MainWindow::sendDataClicked: function that handles click of Send button
 * @param none
 * @return none
 */
void MainWindow::sendDataClicked() {

    if    (!this -> pCoeffEdit -> text().isEmpty()
        && !this -> iCoeffEdit -> text().isEmpty()
        && !this -> dCoeffEdit -> text().isEmpty()
        && !this -> correctionEdit -> text().isEmpty()) {

        if (serialDriver -> openedSuccesfully() && (modeSelector -> currentText() == MODE_94_LABEL)) {

            float pToSend = (this -> pCoeffEdit -> text()).toFloat();
            float iToSend = (this -> iCoeffEdit -> text()).toFloat();
            float dToSend = (this -> dCoeffEdit -> text()).toFloat();
            float correctionToSend = (this -> correctionEdit -> text()).toFloat();

            serialDriver -> sendCommand(pToSend, iToSend, dToSend, correctionToSend, 2070, WRITE_DATA_TO_RAM_COMMAND_94);

            console -> appendPlainText(DATA_SENT_TO_RAM);

        }

        /** not tested **/
        else if (serialDriver -> openedSuccesfully() && (modeSelector -> currentText() == MODE_114_LABEL)) {

            float pToSend = (this -> pCoeffEdit -> text()).toFloat();
            float iToSend = (this -> iCoeffEdit -> text()).toFloat();
            float dToSend = (this -> dCoeffEdit -> text()).toFloat();
            float correctionToSend = (this -> correctionEdit -> text()).toFloat();

            serialDriver -> sendCommand(pToSend, iToSend, dToSend, correctionToSend, 3500, WRITE_DATA_TO_RAM_COMMAND_114);

            console -> appendPlainText(DATA_SENT_TO_RAM);



        }
        /****************************************************************/

    }

    else {

        return;

    }


}

/**
 * @brief MainWindow::switchClicked94: function that sends command to switch to 94 dB mode
 * @param none
 * @return none
 */
void MainWindow::switchClicked94() {

    if (serialDriver->openedSuccesfully()) {

        serialDriver -> sendCommand(0, 0, 0, 0, 0, SWITCH_TO_94_COMMAND);

    }

    console -> appendPlainText(SWITCHED_TO_94_LABEL);

}

/**
 * @brief MainWindow::switchClicked114
 * @param none
 * @return none
 */
void MainWindow::switchClicked114() {

    if(serialDriver -> openedSuccesfully()) {

        serialDriver -> sendCommand(0, 0, 0, 0, 0, SWITCH_TO_114_COMMAND);

    }

    console -> appendPlainText(SWITCHED_TO_114_LABEL);

}

/**
 * @brief MainWindow::closeClicked
 * @param none
 * @return none
 */
void MainWindow::closeClicked() {

    // freeing memory which was allocated for serialDriver
    delete (this -> serialDriver);
    this -> close();

}
