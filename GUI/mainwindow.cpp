#include "mainwindow.h"

MainWindow::MainWindow()
{
    initWindow();

    // For now, change this port to whatever the Arduino is connected to
    initPort("/dev/ttyACM0");

    connect(calibrate_, SIGNAL(clicked()), this, SLOT(calibrateOD()));
    connect(port_, SIGNAL(readyRead()), this, SLOT(readData()));
    requestData();
}

MainWindow::~MainWindow()
{
    closePort();
}

// Initializes all GUI elements of the program
void MainWindow::initWindow()
{
    lcd_temp_ = new QLabel("0");
    lcd_od_ = new QLabel("0");
    lcd_do_ = new QLabel("0");
    lcd_ph_ = new QLabel("0");
    temp_ = new QLabel("Temperature");
    od_ = new QLabel("OD");
    do_ = new QLabel("DO");
    ph_ = new QLabel("pH");
    calibrate_ = new QPushButton("Calibrate");
    grid_layout_ = new QGridLayout();
    grid_layout_->addWidget(temp_, 0, 0);
    grid_layout_->addWidget(od_, 0, 1);
    grid_layout_->addWidget(do_, 2, 0);
    grid_layout_->addWidget(ph_, 2, 1);
    grid_layout_->addWidget(lcd_temp_, 1, 0);
    grid_layout_->addWidget(lcd_od_, 1, 1);
    grid_layout_->addWidget(lcd_do_, 3, 0);
    grid_layout_->addWidget(lcd_ph_, 3, 1);
    grid_layout_->addWidget(calibrate_, 1, 2);
    setLayout(grid_layout_);
    setWindowTitle("GUI");
}

// Initializes the port that will be read and witten to
// TODO: Multiport functionality for the GUI and core program; error handling
void MainWindow::initPort(const char *port)
{
    port_ = new QSerialPort(port, this);
    port_->setBaudRate(QSerialPort::Baud9600);
    port_->setFlowControl(QSerialPort::NoFlowControl);
    port_->setParity(QSerialPort::NoParity);
    port_->setDataBits(QSerialPort::Data8);
    port_->setStopBits(QSerialPort::OneStop);
    port_->open(QIODevice::ReadWrite);
}

void MainWindow::closePort()
{
    port_->close();
}

void MainWindow::configure(BCommunication::ConfigType config_type) {
    port_->putChar(BCommunication::Config);
    port_->putChar(config_type);
}

// Called when data is available to be read from the Arduino
// TODO: move to a non-GUI thread
void MainWindow::readData()
{
    char c;

    if (!port_->canReadLine())
        return;
    port_->getChar(&c);
    BCommunication::PacketType packet_type = (BCommunication::PacketType) c;
    QString data = port_->readLine();
    data.chop(1);

    switch(packet_type) {
      case BCommunication::Config:

        break;
      case BCommunication::OD:
        lcd_od_->setText(data);
        break;
      case BCommunication::DO:
        lcd_do_->setText(data);
        break;
      case BCommunication::Temperature:
        lcd_temp_->setText(data);
        break;
      case BCommunication::Air:

        break;
      case BCommunication::pH:
        lcd_ph_->setText(data);
        break;
      default:

        break;
    }
}

// Sends a packet to the Arduino requesting a reading from all sensors
void MainWindow::requestData()
{
    port_->putChar(BCommunication::Air);
    port_->putChar(BCommunication::DO);
    port_->putChar(BCommunication::OD);
    port_->putChar(BCommunication::pH);
    port_->putChar(BCommunication::Temperature);
}

// Overloaded function. Requests data of a particular type
void MainWindow::requestData(BCommunication::PacketType packet_type)
{
    port_->putChar(packet_type);
}

void MainWindow::calibrateOD() {
    port_->clear();
    configure(BCommunication::CalibrateOD);
}

// Sends a packet to the Arduino requesting the test cycle to begin for a
// particular chamber
void MainWindow::beginTestCycle(int chamber)
{
    port_->putChar(BCommunication::TestRequest);
    port_->putChar(chamber);
}
