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

MainWindow::~MainWindow() {

    delete(this -> serialDriver);

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

    // connecting Write Memory button
    connect(writeMemoryButton, &QPushButton::clicked, this, &MainWindow::writeMemory);

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

    correctionEdit = new QLineEdit(BIAS_DEFAULT);
    pCoeffEdit     = new QLineEdit(P_DEFAULT);
    iCoeffEdit     = new QLineEdit(I_DEFAULT);
    dCoeffEdit     = new QLineEdit(D_DEFAULT);

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
        writeMemoryButton -> setEnabled(true);

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

    bool okP = false, okI = false, okD = false, okB = false;

    float pToSend = (this -> pCoeffEdit -> text()).toFloat(&okP);
    float iToSend = (this -> iCoeffEdit -> text()).toFloat(&okI);
    float dToSend = (this -> dCoeffEdit -> text()).toFloat(&okD);
    float correctionToSend = (this -> correctionEdit -> text()).toFloat(&okB);

    bool ok = okP & okI & okD &okB;

    if (!ok) {

        console -> appendPlainText(NUMERIC_WARNING);
        return;

    }

    if (modeSelector -> currentText() == MODE_94_LABEL) {

        serialDriver -> sendCommand(pToSend, iToSend, dToSend, correctionToSend, MODE_94_REF, WRITE_DATA_TO_RAM_COMMAND_94);
        console -> appendPlainText(DATA_SENT_TO_RAM);

    }

    else {

        serialDriver -> sendCommand(pToSend, iToSend, dToSend, correctionToSend, MODE_114_REF, WRITE_DATA_TO_RAM_COMMAND_114);
        console -> appendPlainText(DATA_SENT_TO_RAM);

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
 * @brief MainWindow::writeMemory
 * @param
 * @return
 */
void MainWindow::writeMemory() {

    if (serialDriver -> openedSuccesfully()) {

        // wriritng data for 94 dB mode
        if (modeSelector -> currentText() == MODE_94_LABEL) {

            // sending command to write contents of RAM to EEPROM
            serialDriver -> sendCommand(0.0, 0.0, 0.0, 0.0, 0, 0x08);

            console -> appendPlainText(EEPROM_94_LABEL);

        }

        // wriritng data for 114 dB mode
        else {

            serialDriver -> sendCommand(0.0, 0.0, 0.0, 0.0, 0, 0x09);
            console -> appendPlainText(EEPROM_114_LABEL);

        }

    }

}

bool MainWindow::isFloat(QString *text) {

    pidValidator = new QDoubleValidator(-1.0, 1.0, 32, this);
    pidValidator -> setNotation(QDoubleValidator::StandardNotation);

    return false;
}

/**
 * @brief MainWindow::closeClicked
 * @param none
 * @return none
 */
void MainWindow::closeClicked() {

    this -> close();

}
