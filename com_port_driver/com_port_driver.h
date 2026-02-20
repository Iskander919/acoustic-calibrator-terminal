#ifndef COM_PORT_DRIVER_H
#define COM_PORT_DRIVER_H

#include <QWidget>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QList>
#include <array>
#include <bit>
#include <iomanip>
#include <iostream>

#define BAUD_RATE QSerialPort::BaudRate::Baud115200

class SerialDriver {

public:

    SerialDriver();

    void openSerialPort(const QString &portName);

    void sendCommand(const float pCoeff, const float iCoeff, const float dCoeff, const float corr,
                                                                                 const uint32_t ref,
                                                                                 const uint8_t command);

    bool openedSuccesfully();

    std::array<uint8_t, 20> combineArray(const float pCoeff, const float iCoeff,  const float dCoeff,
                                                                                  const float corr,
                                                                                  const uint32_t ref);

    void readBytes();

    void parseBytes(QString *pSoftwareVersion, QString *pDeviceId);

    int getReceiveBufferSize();

    QSerialPort *SerialPortObj;

    QByteArray receivedBytes;

    void clearInputBuffer();

    void clearOutputBuffer();

    uint32_t getChecksum();


private:

    // array that stores bytes to send
    std::array<uint8_t, 20> data;

    // variable that stores a command to send
    uint8_t command;

    // variable that stores status of COM Port (whether opening was succesful)
    bool ok;

    // variable that stores checksum
    uint32_t checksum;

    uint32_t calculateChecksum(QByteArray arrayToSend);

};

#endif // COM_PORT_DRIVER_H
