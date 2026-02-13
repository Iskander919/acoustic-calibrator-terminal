#include "infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) : QMainWindow{parent} {

    setupUi();
    setupConnections();

}


InfoWindow::~InfoWindow() {


}

void InfoWindow::setupUi() {

    QWidget *central = new QWidget(this);

    text = new QTextEdit(TEXT_INFO);

    setCentralWidget(central);

    layout = new QVBoxLayout(central);

    closeButton = new QPushButton(CLOSE_INFO_BUTTON_LABEL);

    layout -> addWidget(text);
    layout -> addWidget(closeButton);


}


void InfoWindow::setupConnections() {

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

}
