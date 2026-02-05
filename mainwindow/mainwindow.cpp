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

    setupLayouts(central);

    setFixedSize(600, 400);
}

/**
 * @brief MainWindow::setupConnections
 */
void MainWindow::setupConnections() {

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);


}

void MainWindow::setupLayouts(QWidget *widget) {

    QVBoxLayout *buttonsLayout = new QVBoxLayout(widget);

    buttonsLayout -> setContentsMargins(10, 10, 420, 10);

    // implememnting buttons of main window:
    setConnectionButton = new QPushButton(CONNECT_BUTTON_LABEL);
    setCoeffsButton     = new QPushButton(SET_COEFFS_BUTTON_LABEL);
    writeMemoryButton   = new QPushButton(WRITE_MEM_BUTTON_LABEL);
    eraseMemoryButton   = new QPushButton(ERASE_MEM_BUTTON_LABEL);
    closeButton         = new QPushButton(CLOSE_BUTTON_LABEL);

    // adding buttons to layout:
    buttonsLayout -> addWidget(setConnectionButton);
    buttonsLayout -> addWidget(setCoeffsButton);
    buttonsLayout -> addWidget(writeMemoryButton);
    buttonsLayout -> addWidget(eraseMemoryButton);
    buttonsLayout -> addWidget(closeButton);

}
