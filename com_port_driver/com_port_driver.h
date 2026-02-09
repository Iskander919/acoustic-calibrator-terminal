#ifndef COM_PORT_DRIVER_H
#define COM_PORT_DRIVER_H

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QList>

#define BAUD_RATE QSerialPort::BaudRate::Baud115200

class SerialDriver {

public:

    SerialDriver();

    void openSerialPort(const QString &portName);

private:

    QSerialPort *SerialPortObj;

};

#endif // COM_PORT_DRIVER_H
