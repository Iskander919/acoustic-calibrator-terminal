#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

class InfoWindow : public QMainWindow {
public:

    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();

private:

    QTextEdit *text = nullptr;
    QPushButton *closeButton = nullptr;


};

#endif // INFOWINDOW_H
