#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "Communication.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void readData();
    void requestData();
    void requestData(BCommunication::PacketType packet_type);
    void beginTestCycle(int chamber);

private:
    void initWindow();
    void initPort(const char *port);
    void closePort();
    QLabel *lcd_temp_, *lcd_od_, *lcd_do_, *lcd_ph_;
    QLabel *temp_, *od_, *do_, *ph_;
    QGridLayout *grid_layout_;
    QSerialPort *port_;
};

#endif // MAINWINDOW_H
