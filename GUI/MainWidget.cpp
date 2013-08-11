#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QtDebug>

MainWidget::MainWidget(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWidget)
{
    ui->setup(this);
    serial = new QSerialPort(this);

	ui->actionConnect->setEnabled(true);
	ui->actionDisconnect->setEnabled(false);
	ui->actionExit->setEnabled(true);

    initActionsConnections();
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    ui->statusBar->showMessage(tr("Ready"));
}

void MainWidget::openSerialPort()
{
	serial->setPortName("ttyACM0");
    qDebug() <<"Opening serial "<<serial->open(QIODevice::ReadWrite);
    qDebug() <<"Setting Baud Rate " << serial->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
    if(serial->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections))
            qDebug() << "Done setting baud rate";
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    ui->actionConnect->setEnabled(false);
    ui->actionDisconnect->setEnabled(true);


    ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                               .arg(serial->portName()).arg(serial->baudRate()).arg(serial->dataBits())
                               .arg(serial->parity()).arg(serial->stopBits()).arg(serial->flowControl()));
}

void MainWidget::readData()
{

	 char c;

    if (!serial->canReadLine())
        return;
    serial->getChar(&c);
    BCommunication::PacketType packet_type = (BCommunication::PacketType) c;
    QString data = serial->readLine();
    data.chop(1);

    switch(packet_type) {
      case BCommunication::Config:

        break;
      case BCommunication::OD:
        ui->monitor->lcd_OD->display(data.toInt());
        break;
      case BCommunication::DO:
        ui->monitor->lcd_DO->display(data.toInt());
        break;
      case BCommunication::Temperature:
        ui->monitor->lcd_temp->display(data.toInt());
        break;
      case BCommunication::Air:

        break;
      case BCommunication::pH:
        ui->monitor->lcd_pH->display(data.toInt());        
        break;
      default:

        break;
    }
   
}

void MainWidget::closeSerialPort()
{
	serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWidget::initActionsConnections()
{
	connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
	connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}

void MainWidget::requestData()
{
    serial->putChar(BCommunication::Air);
    serial->putChar(BCommunication::DO);
    serial->putChar(BCommunication::OD);
    serial->putChar(BCommunication::pH);
    serial->putChar(BCommunication::Temperature);
}

void MainWidget::configure(BCommunication::ConfigType config_type) 
{
    serial->putChar(BCommunication::Config);
    serial->putChar(config_type);
}

void MainWidget::requestData(BCommunication::PacketType packet_type)
{
    serial->putChar(packet_type);
}

void MainWidget::calibrateOD()
 {
    configure(BCommunication::CalibrateOD);
}

void MainWidget::setTemperature(float temperature)
{
	configure(BCommunication::SetTemperature);
    serial->write(reinterpret_cast<const char*>(&temperature), sizeof(temperature));
    serial->putChar('\n');
}

void MainWidget::beginTestCycle(int chamber)
{
    serial->putChar(BCommunication::TestRequest);
    serial->putChar(chamber);
}


MainWidget::~MainWidget()
{
    delete ui;
}
