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

    void sendCommand(const uint8_t data[20], const uint8_t command);

    std::array<uint8_t, 20> combineArray(const float pCoeff, const float iCoeff, const float dCoeff,
                                                                                  const float corr,
                                                                                  const uint32_t ref);

private:

    QSerialPort *SerialPortObj;

    std::array<uint8_t, 20> data;
    uint8_t command;

};

#endif // COM_PORT_DRIVER_H
