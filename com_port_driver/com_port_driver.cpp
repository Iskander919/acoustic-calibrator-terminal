#include "com_port_driver.h"

/**
 * @brief SerialDriver::SerialDriver
 */
SerialDriver::SerialDriver() {

    this -> SerialPortObj = new QSerialPort();

}

/**
 * @brief SerialDriver::openSerialPort
 * @param portName
 */
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

/**
 * @brief SerialDriver::combineArray
 * @param pCoeff
 * @param iCoeff
 * @param dCoeff
 * @param corr
 * @param ref
 * @return
 */
std::array<uint8_t, 20> SerialDriver::combineArray(const float pCoeff, const float iCoeff, const float dCoeff,
                                     const float corr, const uint32_t ref) {

    std::array<uint8_t, 20> result;

    // getting bytes from pCoeff float and storing them to array
    std::array<uint8_t, 4> pBytes = std::bit_cast<std::array<uint8_t, 4>>(pCoeff);

    // getting bytes from iCoeff
    std::array<uint8_t, 4> iBytes = std::bit_cast<std::array<uint8_t, 4>>(iCoeff);

    // getting bytes from dCoeff
    std::array<uint8_t, 4> dBytes = std::bit_cast<std::array<uint8_t, 4>>(dCoeff);

    // getting bytes from corr
    std::array<uint8_t, 4> corrBytes = std::bit_cast<std::array<uint8_t, 4>>(corr);

    // getting bytes from ref
    std::array<uint8_t, 4> refBytes  = std::bit_cast<std::array<uint8_t, 4>>(ref);

    // filling result:
    for(int i = 0; i < 4; i++) {

        result[i] = pBytes[i];
    }

    for(int i = 0; i < 4; i++) {

        result[i + 4] = iBytes[i];
    }

    for(int i = 0; i < 4; i++) {

        result[i + 8] = dBytes[i];
    }

    for(int i = 0; i < 4; i++) {

        result[i + 12] = corrBytes[i];
    }

    for(int i = 0; i < 4; i++) {

        result[i + 16] = refBytes[i];
    }

    return result;

}
