#ifndef INFOWINDOW_H
#define INFOWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#define CLOSE_INFO_BUTTON_LABEL "Закрыть"

#define TEXT_INFO "Info"

#define INFO_WIDTH  500
#define INFO_HEIGHT 500

class InfoWindow : public QMainWindow {
public:

    explicit InfoWindow(QWidget *parent = nullptr);
    ~InfoWindow();

    void setupUi();
    void setupConnections();

private:

    QVBoxLayout *layout = nullptr;

    QTextEdit *text = nullptr;
    QPushButton *closeButton = nullptr;


};

#endif // INFOWINDOW_H
