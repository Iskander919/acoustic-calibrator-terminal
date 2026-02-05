#include "mainwindow.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {


    setupUi();
    setupConnections();

}

/**
 * @brief MainWindow::setupUi
 */
void MainWindow::setupUi() {

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    setFixedSize(600, 400);

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

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);


}

/**
 * @brief MainWindow::setupButtonLayout
 * @param
 */
void MainWindow::setupButtonLayout() {

    buttonLayout = new QVBoxLayout();

    // implememnting buttons of main window:
    setConnectionButton = new QPushButton(CONNECT_BUTTON_LABEL);
    setCoeffsButton     = new QPushButton(SET_COEFFS_BUTTON_LABEL);
    writeMemoryButton   = new QPushButton(WRITE_MEM_BUTTON_LABEL);
    eraseMemoryButton   = new QPushButton(ERASE_MEM_BUTTON_LABEL);
    closeButton         = new QPushButton(CLOSE_BUTTON_LABEL);

    // adding buttons to layout:
    buttonLayout -> addWidget(setConnectionButton);
    buttonLayout -> addWidget(setCoeffsButton);
    buttonLayout -> addWidget(writeMemoryButton);
    buttonLayout -> addWidget(eraseMemoryButton);
    buttonLayout -> addWidget(closeButton);

}

/**
 * @brief MainWindow::setupConsoleLayout
 * @param parentWidget
 */
void MainWindow::setupConsoleLayout() {

    consoleLayout = new QVBoxLayout();

    QPlainTextEdit *console = new QPlainTextEdit();

    console -> setReadOnly(true);

    consoleLayout -> addWidget(console);

}


