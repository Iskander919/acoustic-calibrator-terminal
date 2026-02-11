#include "mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {


    setupUi();
    setupConnections();

    serial = new QSerialPort();

    updatePortsList();

}

/**
 * @brief MainWindow::setupUi
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
 */
void MainWindow::setupConnections() {

    // connecting Close button
    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);


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
}

/**
 * @brief MainWindow::setupButtonLayout
 * @param
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
 */
void MainWindow::connectClicked() {

    serialDriver = new SerialDriver;

    // getting COM Port number from comPortSelector(ComboBox) and opening it
    serialDriver -> openSerialPort(this -> comPortSelector -> currentText());

    // writing message to console:
    if (serialDriver -> openedSuccesfully()) {

        console -> appendPlainText(CONNECTION_SUCCESS_LABEL + (this -> comPortSelector -> currentText()));
        setModeButton94   -> setEnabled(true);
        setModeButton114  -> setEnabled(true);

    }

    //---------------------------------------------------------------------------//
    std::array<uint8_t, 20> combined = serialDriver -> combineArray(0.00001, 0.0000015, 0.00001, 0.000245, 3500);
    for(int i = 0; i < 20; i++) {

        std::cout << std::hex << std::setw(3) << static_cast<int>(combined[i]);

    }

    std::cout << std::endl;

    //---------------------------------------------------------------------------//

}

/**
 * @brief MainWindow::sendDataClicked
 */
void MainWindow::sendDataClicked() {

    if(this -> modeSelector -> currentText() == MODE_94_LABEL) {


    }

    else {


    }


}

/**
 * @brief MainWindow::switchClicked94: function that sends command to switch to 94 dB mode
 * @param none
 * @return none
 */
void MainWindow::switchClicked94() {

    if(serialDriver->openedSuccesfully()) {

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
