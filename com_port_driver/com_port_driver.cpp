#include "com_port_driver.h"

SerialDriver::SerialDriver() {

    this -> SerialPortObj = new QSerialPort();

}

void SerialDriver::openSerialPort(const QString &portName) {

    this -> SerialPortObj -> setPortName(portName);
    this -> SerialPortObj -> setBaudRate(BAUD_RATE);


}
