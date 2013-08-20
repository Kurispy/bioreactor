#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "Communication.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

signals:
    void intToDouble(double);
    void doubleToInt(int);
    void doubleToFloat(float);


public slots:
    void readData();
    void requestData();
    void requestData(BCommunication::PacketType packet_type);
    void calibrateOD();
    void setTemperature(float temperature);
    void setSolenoidState(bool on);
    void setMotorState(bool on);
    void setMotorSpeed(int rpm);
    void beginTestCycle(int chamber);
    void intToDouble(int value);
    void doubleToInt(double value);
    void doubleToFloat(double value);

private:
    void initWindow();
    void initPort(const char *port);
    void closePort();
    void configure(BCommunication::ConfigType config_type);
    QLabel *temp_display_, *od_display_, *do_display_, *ph_display_;
    QLabel *temp_, *od_, *do_, *ph_;
    QGridLayout *grid_layout_;
    QSerialPort *port_;
    QPushButton *calibrate_od_button_;
    QCheckBox *solenoid_switch_, *motor_switch_;
    QSlider *temperature_slider_, *motor_rpm_slider_;
    QDoubleSpinBox *temperature_spin_box_;
    QSpinBox *motor_rpm_spin_box_;
};

#endif // MAINWINDOW_H
