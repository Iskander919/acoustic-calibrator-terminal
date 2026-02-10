#ifndef COM_PORT_DRIVER_H
#define COM_PORT_DRIVER_H

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QList>
#include <array>
#include <bit>

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

private:

    QSerialPort *SerialPortObj;

    // array that stores bytes to send
    std::array<uint8_t, 20> data;

    // variable that stores a command to send
    uint8_t command;

    // variable that stores status of COM Port (whether opening was succesful)
    bool ok;

};

#endif // COM_PORT_DRIVER_H
