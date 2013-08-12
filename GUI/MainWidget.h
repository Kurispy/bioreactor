#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "Communication.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLCDNumber>
#include <QtSerialPort/QSerialPort>


namespace Ui
{
	class MainWidget;
}

class MainWidget : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    void readData();
	void requestData();
    void calibrateOD();
    void openSerialPort();
    void closeSerialPort();
    void requestData(BCommunication::PacketType packet_type);

    void setTemperature(float temperature);
    void beginTestCycle(int chamber);

private:
    void initActionsConnections();
    void configure(BCommunication::ConfigType config_type);

private:
    Ui::MainWidget *ui;
    QSerialPort *serial;
};

#endif

