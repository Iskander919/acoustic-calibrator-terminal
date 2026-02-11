#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main_window_labels.h"
#include "com_port_driver.h"

#include <iomanip>
#include <iostream>


#include <QMainWindow>
#include <QApplication>
#include <QComboBox>
#include <QFont>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    // declaring buttons:
    QPushButton *setConnectionButton = nullptr;
    QPushButton *setModeButton94     = nullptr;
    QPushButton *setModeButton114    = nullptr;
    QPushButton *eraseMemoryButton   = nullptr;
    QPushButton *writeMemoryButton   = nullptr;
    QPushButton *setCoeffsButton     = nullptr;
    QPushButton *closeButton         = nullptr;

    QComboBox *comPortSelector       = nullptr;
    QComboBox *modeSelector          = nullptr;

private:

    // ui setup functions:
    void setupUi();
    void setupConnections();

    void setupLayouts(QWidget *parentWidget);

    void setupButtonLayout();
    void setupConsoleLayout();

    void setupLineEdits();

    void updatePortsList();

    // declaring slots:
    void connectClicked();
    void sendDataClicked();

    void switchClicked94();
    void switchClicked114();

    void closeClicked();

    // defining layouts:
    QHBoxLayout *mainLayout    = nullptr;
    QVBoxLayout *buttonLayout  = nullptr;
    QVBoxLayout *consoleLayout = nullptr;

    // defining line edits:
    QLineEdit *correctionEdit = nullptr;
    QLineEdit *pCoeffEdit     = nullptr;
    QLineEdit *iCoeffEdit     = nullptr;
    QLineEdit *dCoeffEdit     = nullptr;

    // defining console:
    QPlainTextEdit *console = nullptr;

    // defining serial port object:
    QSerialPort *serial = nullptr;
    QTimer      *timer  = nullptr;

    // defining list of available ports:
    QList<QSerialPortInfo> portsList;

    // creating SerialDriver object:
    SerialDriver *serialDriver = nullptr;


};

#endif // MAINWINDOW_H
