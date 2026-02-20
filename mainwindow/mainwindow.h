#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "infowindow.h"
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
#include <QValidator>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // declaring buttons:
    QPushButton *setConnectionButton = nullptr;
    QPushButton *setModeButton94     = nullptr;
    QPushButton *setModeButton114    = nullptr;
    QPushButton *eraseMemoryButton   = nullptr;
    QPushButton *writeMemoryButton   = nullptr;
    QPushButton *setCoeffsButton     = nullptr;
    QPushButton *infoButton          = nullptr;
    QPushButton *closeButton         = nullptr;

    QPushButton *readDeviceDataButton  = nullptr;
    QPushButton *writeDeviceDataButton = nullptr;

    QComboBox *comPortSelector       = nullptr;
    QComboBox *modeSelector          = nullptr;

private:

    // ui setup functions:
    void setupUi();
    void setupConnections();

    void setupLayouts(QWidget *parentWidget);

    // layouts setup functions:
    void setupButtonLayout();
    void setupConsoleLayout();
    void setupDeviceDataLayout();

    void setupLineEdits();

    void updatePortsList();

    bool isFloat(QString *text);

    void convertReadBytesToStrings();

    void updateDeviceInfoLines(); // update line edits with device id and software version

    void updateChecksumLineEdit();

    // declaring slots:
    void connectClicked();  // "Connect" clicked handler
    void sendDataClicked(); // "Send" clicked handler

    void switchClicked94(); // "Switch to 94" clicked handler
    void switchClicked114();// "Switch to 114" clicked handler

    void writeMemory();     // "Write to memory" clicked (EEPROM) handler

    void closeClicked();    // "Close" clicked handler

    void infoClicked();     // "Info" clicked handler

    void modeSelectorChanged();   // handler of signal of changed option in mode selector

    void writeIdClicked();        // "Write ID" clicked handler

    void readDeviceDataClicked(); // "Read Device Data" clicked handler

    void updateWriteIdButton();   // function that updates "Write ID" button when text in ID line edit changes

    void deviceIdTextChanged();   // handler of changing text in device ID line edit


    // defining layouts:
    QHBoxLayout *mainLayout       = nullptr;
    QVBoxLayout *buttonLayout     = nullptr;
    QVBoxLayout *deviceDataLayout = nullptr;
    QVBoxLayout *consoleLayout    = nullptr;

    // defining line edits for tuning:
    QLineEdit *correctionEdit = nullptr;
    QLineEdit *pCoeffEdit     = nullptr;
    QLineEdit *iCoeffEdit     = nullptr;
    QLineEdit *dCoeffEdit     = nullptr;

    // defining line edits for device and software data
    QLineEdit *deviceNumberEdit    = nullptr;
    QLineEdit *softwareVersionEdit = nullptr;
    QLineEdit *checksumEdit        = nullptr;

    // defining console:
    QPlainTextEdit *console = nullptr;

    // defining serial port object:
    QSerialPort *serial = nullptr;
    QTimer      *timer  = nullptr;

    // defining list of available ports:
    QList<QSerialPortInfo> portsList;

    // creating SerialDriver object:
    SerialDriver *serialDriver = nullptr;

    // validator for line edits
    QDoubleValidator *pidValidator = nullptr;

    InfoWindow *infoWindow = nullptr;

    // strings to show in line edits
    QString softwareVersion;
    QString deviceId;

};

#endif // MAINWINDOW_H
