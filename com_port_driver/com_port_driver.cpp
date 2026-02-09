#include "com_port_driver.h"

SerialDriver::SerialDriver() {

    this -> SerialPortObj = new QSerialPort();

}

void SerialDriver::openSerialPort(const QString &portName) {

    this -> SerialPortObj -> setPortName(portName);
    this -> SerialPortObj -> setBaudRate(BAUD_RATE);
    this -> SerialPortObj -> setParity(QSerialPort::Parity::NoParity);
    this -> SerialPortObj -> setDataBits(QSerialPort::DataBits::Data8);
    this -> SerialPortObj -> setStopBits(QSerialPort::StopBits::OneStop);
    this -> SerialPortObj -> setFlowControl(QSerialPort::FlowControl::HardwareControl);

    this -> SerialPortObj -> open(QIODevice::ReadWrite);

    if (!this -> SerialPortObj -> isOpen()) {

        qDebug() << "COM Port Error: " << this -> SerialPortObj -> error();

    }

}
