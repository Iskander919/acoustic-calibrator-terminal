#ifndef COM_PORT_DRIVER_H
#define COM_PORT_DRIVER_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>

class SerialDriver {

public:

    SerialDriver();

    void openSerialPort();

};

#endif // COM_PORT_DRIVER_H
