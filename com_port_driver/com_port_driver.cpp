#include "com_port_driver.h"

/**
 * @brief SerialDriver::SerialDriver
 */
SerialDriver::SerialDriver() {

    this -> SerialPortObj = new QSerialPort();
    this -> ok = false;

    receivedBytes = {};

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
        this -> ok = false;

    }

    else {

        qDebug() << "Opening successful";
        this -> ok = true;

    }

}

/**
 * @brief SerialDriver::combineArray
 * @param pCoeff
 * @param iCoeff
 * @param dCoeff
 * @param corr
 * @param ref
 * @return none
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

        result[3 - i] = pBytes[i];

    }

    for(int i = 0; i < 4; i++) {

        result[7 - i] = iBytes[i];

    }

    for(int i = 0; i < 4; i++) {

        result[11 - i] = dBytes[i];

    }

    for(int i = 0; i < 4; i++) {

        result[15 - i] = corrBytes[i];

    }

    for(int i = 0; i < 4; i++) {

        result[19 - i] = refBytes[i];

    }

    return result;

}

/**
 * @brief SerialDriver::sendCommand
 * @param data
 * @param command
 */
void SerialDriver::sendCommand(const float pCoeff, const float iCoeff, const float dCoeff,
                               const float corr,
                               const uint32_t ref, uint8_t command) {

    std::array<uint8_t, 20> toSend = combineArray(pCoeff, iCoeff, dCoeff, corr, ref);
    QByteArray qToSend;

    // converting std::array to QByteArray
    for(int i = 0; i < toSend.size(); i++) {

        qToSend.append(toSend[i]);

    }

    // appending command to the end of array
    qToSend.append(command);

    for(int i = 0; i < qToSend.size(); i++) {

        std::cout << std::hex << std::setw(2) << static_cast<int>(qToSend[i]) << " ";

    }

    std::cout << std::endl;

    // writing data to serial port:
    qint64 bytesWritten = SerialPortObj -> write(qToSend);

    if(SerialPortObj -> waitForBytesWritten(500)) {

        qDebug() << "Bytes written successfully";

    }

    else {

        qDebug() << "Failed to write to serial port" << SerialPortObj -> errorString();

    }
}

/**
 * @brief SerialDriver::openedSuccesfully
 * @return
 */
bool SerialDriver::openedSuccesfully() {

    return this -> ok;

}

/**
 * @brief SerialDriver::readBytes
 * @param none
 * @return std::array<uint8_t, 20> result
 */
void SerialDriver::readBytes() {

    std::array<uint8_t, 20> result = {};

    QByteArray serialData = SerialPortObj -> readAll();

    this -> receivedBytes = serialData;

}

/**
 * @brief parseBytes
 * @param pSoftwareVersion
 * @param pDeviceId
 */
void SerialDriver::parseBytes(QString *pSoftwareVersion, QString *pDeviceId) {

    QByteArray bytes = this -> receivedBytes;

    std::array<uint8_t, 4> softVerArray = {};
    std::array<uint8_t, 4> deviceIdArray = {};

    for (int i = 0; i < softVerArray.size(); i++) {

        softVerArray[i] = bytes[16 + i];

    }

    for (int i = 0; i < deviceIdArray.size(); i++) {

        deviceIdArray[i] = bytes[15 - i];

    }


    /*----------------------------------------*/
    for (int i = 0; i < softVerArray.size(); i++) {

        std::cout << std::hex << std::setw(3) << static_cast<int>(softVerArray[i]) << " ";

    }

    std::cout << std::endl;

    for (int i = 0; i < deviceIdArray.size(); i++) {

        std::cout << std::hex << std::setw(3) << static_cast<int>(deviceIdArray[i]) << " ";

    }
    /*----------------------------------------*/

    // building deviceId and version from bytes
    uint32_t deviceId = std::bit_cast<uint32_t>(deviceIdArray);
    float    version  = std::bit_cast<float>(softVerArray);

    *pDeviceId        = QString::number(deviceId);
    *pSoftwareVersion = QString::number(version, 'f', 1);

    /*----------------------------------------*/
    qDebug() << "version: "  << *pSoftwareVersion;
    qDebug() << "deviceId: " << *pDeviceId;
    /*----------------------------------------*/

 }

/**
 * @brief SerialDriver::getReceiveBufferSize
 * @return
 */
int SerialDriver::getReceiveBufferSize() {

    return this -> receivedBytes.size();

}

/**
 * @brief SerialDriver::clearInputBuffer
 */
void SerialDriver::clearInputBuffer() {

    SerialPortObj -> clear(QSerialPort::Input);

}
