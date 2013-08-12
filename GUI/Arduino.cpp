#include "Arduino.h"

Arduino::Arduino(QSerialPort::BaudRate baud_rate,
                 QSerialPort::FlowControl flow_control,
                 QSerialPort::Parity parity,
                 QSerialPort::DataBits data_bits,
                 QSerialPort::StopBits stop_bits)
{
    setBaudRate(baud_rate);
    setFlowControl(flow_control);
    setParity(parity);
    setDataBits(data_bits);
    setStopBits(stop_bits);

    connect(this, SIGNAL(readyRead()), this, SLOT(readData()));
}

void Arduino::configure(BCommunication::ConfigType config_type) {
    putChar(BCommunication::Config);
    putChar(config_type);
}

// Called when data is available to be read from the Arduino
// Emits a dataReady signal when a complete data packet has been received
void Arduino::readData()
{
    QString *data;
    if (!canReadLine())
        return;
    data = new QString(readLine());
    emit dataReady(data);
}

// Sends a packet to the Arduino requesting a reading from all sensors
void Arduino::requestData()
{
    putChar(BCommunication::Air);
    putChar(BCommunication::DO);
    putChar(BCommunication::OD);
    putChar(BCommunication::pH);
    putChar(BCommunication::Temperature);
}

// Overloaded function. Requests data of a particular type
void Arduino::requestData(BCommunication::PacketType packet_type)
{
    putChar(packet_type);
}

// Requests the Arduino to zero the OD
void Arduino::calibrateOD() {
    configure(BCommunication::CalibrateOD);
}

// Sends a desired temperature to the Arduino
void Arduino::setTemperature(float temperature) {
    configure(BCommunication::SetTemperature);
    write(reinterpret_cast<const char*>(&temperature), sizeof(temperature));
    putChar('\n');
}

// Sends a packet to the Arduino requesting the test cycle to begin for a
// particular chamber
void Arduino::beginTestCycle(int chamber)
{
    putChar(BCommunication::TestRequest);
    putChar(chamber);
}
