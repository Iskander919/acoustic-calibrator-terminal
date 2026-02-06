#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main_window_labels.h"


#include <QMainWindow>
#include <QApplication>
#include <QComboBox>
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
    QPushButton *eraseMemoryButton   = nullptr;
    QPushButton *writeMemoryButton   = nullptr;
    QPushButton *setCoeffsButton     = nullptr;
    QPushButton *closeButton         = nullptr;

    QComboBox *comPortSelector       = nullptr;

private:

    void setupUi();
    void setupConnections();

    void setupLayouts(QWidget *parentWidget);

    void setupButtonLayout();
    void setupConsoleLayout();

    void updatePortsList();

    void setupTimer();

    // defining layouts:
    QHBoxLayout *mainLayout = nullptr;
    QVBoxLayout *buttonLayout = nullptr;
    QVBoxLayout *consoleLayout = nullptr;

    // defining line edits:
    QLineEdit *correctionEdit = nullptr;
    QLineEdit *pCoeffEdit     = nullptr;
    QLineEdit *iCoeffEdit     = nullptr;
    QLineEdit *dCoeffEdit     = nullptr;


    // defining serial port object:
    QSerialPort *serial = nullptr;
    QTimer      *timer  = nullptr;

    // defining list of available ports:
    QList<QSerialPortInfo> portsList;


};

#endif // MAINWINDOW_H
