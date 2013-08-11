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
MainWidget::~MainWidget()
{
    delete ui;
}
