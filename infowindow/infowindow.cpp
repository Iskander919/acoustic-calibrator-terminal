#include "infowindow.h"

InfoWindow::InfoWindow(QWidget *parent) : QMainWindow{parent} {

    setupUi();
    setupConnections();

}


InfoWindow::~InfoWindow() {


}

void InfoWindow::setupUi() {

    QWidget *central = new QWidget(this);

    //resize(INFO_WIDTH, INFO_HEIGHT);
    setFixedSize(INFO_WIDTH, INFO_HEIGHT);

    QString info = TEXT_INFO;

    text = new QTextEdit();
    text -> setReadOnly(true);
    // describe left section
    text -> append("<h2> Левое меню </h2>");
    text -> append("<p> Выпадающие меню позволяют выбрать COM-порт и режим, для которого производится запись параметров. </p1>");
    text -> append("<p> Кнопка Отправить позволяет записать данные в оперативную память, но не в постоянную память. </p1>");
    text -> append("<p> Кнопка Записать данные в память позволяет записать данные в постоянную память (для выбранного режима). </p1>");

    // describe central section
    text -> append("<h2> Центральное меню </h2>");
    text -> append("<p> Кнопка Прочитать позволяет прочитать версию ПО и серийный номер. </p1>");
    text -> append("<p> Кнопка Записать позволяет записать в постоянную память серийный номер. </p1>");

    // describe right section
    text -> append("<h2> Правое меню </h2>");
    text -> append("<p> В поля можно ввести значение уровня и значения коэффициентов ПИД-регулятора. </p1>");
    text -> append("<p> Для режима 94 дБ рекомендуемые значения уровня 0.090...0.11 (по умолчанию 0.098) </p1>");
    text -> append("<p> Для режима 114 дБ рекомендуемые значения уровня 0.000230...0.000260 (по умолчанию 0.000245) </p1>");


    setCentralWidget(central);

    layout = new QVBoxLayout(central);

    closeButton = new QPushButton(CLOSE_INFO_BUTTON_LABEL);

    layout -> addWidget(text);
    layout -> addWidget(closeButton);


}


void InfoWindow::setupConnections() {

    connect(closeButton, &QPushButton::clicked, this, &QWidget::close);

}
