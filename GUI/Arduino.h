#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include "Communication.h"

class Arduino : public QSerialPort
{
    Q_OBJECT

public:
    Arduino(QSerialPort::BaudRate baud_rate = QSerialPort::Baud9600,
            QSerialPort::FlowControl flow_control = QSerialPort::NoFlowControl,
            QSerialPort::Parity parity = QSerialPort::NoParity,
            QSerialPort::DataBits data_bits = QSerialPort::Data8,
            QSerialPort::StopBits stop_bits = QSerialPort::OneStop);
    
signals:
    void dataReady(QString *data);
    
public slots:
    void requestData();
    void requestData(BCommunication::PacketType packet_type);
    void calibrateOD();
    void setTemperature(float temperature);
    void beginTestCycle(int chamber);

private slots:
    void readData();

private:
    void configure(BCommunication::ConfigType config_type);
};

#endif // ARDUINO_H
