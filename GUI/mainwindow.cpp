#include "mainwindow.h"

MainWindow::MainWindow()
{
    initWindow();

    // For now, change this port to whatever the Arduino is connected to
    initPort("/dev/ttyACM0");

    connect(calibrate_od_button_, SIGNAL(clicked()), this, SLOT(calibrateOD()));
    connect(port_, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(temperature_slider_, SIGNAL(valueChanged(int)), this, SLOT(intToDouble(int)));
    connect(this, SIGNAL(intToDouble(double)), temperature_spin_box_, SLOT(setValue(double)));
    connect(temperature_spin_box_, SIGNAL(valueChanged(double)), this, SLOT(doubleToInt(double)));
    connect(this, SIGNAL(doubleToInt(int)), temperature_slider_, SLOT(setValue(int)));
    connect(temperature_spin_box_, SIGNAL(valueChanged(double)), this, SLOT(doubleToFloat(double)));
    connect(this, SIGNAL(doubleToFloat(float)), this, SLOT(setTemperature(float)));
}

MainWindow::~MainWindow()
{
    closePort();
}

// Initializes all GUI elements of the program
void MainWindow::initWindow()
{
    temp_display_ = new QLabel("0");
    od_display_ = new QLabel("0");
    do_display_ = new QLabel("0");
    ph_display_ = new QLabel("0");
    temp_ = new QLabel("Temperature");
    od_ = new QLabel("OD");
    do_ = new QLabel("DO");
    ph_ = new QLabel("pH");
    calibrate_od_button_ = new QPushButton("Calibrate OD");
    temperature_slider_ = new QSlider(Qt::Vertical);
    temperature_spin_box_ = new QDoubleSpinBox();
    temperature_slider_->setMaximum(30);
    temperature_slider_->setMinimum(10);
    temperature_spin_box_->setRange(10, 30);
    grid_layout_ = new QGridLayout();

    grid_layout_->addWidget(temp_, 0, 0);
    grid_layout_->addWidget(od_, 0, 1);
    grid_layout_->addWidget(do_, 2, 0);
    grid_layout_->addWidget(ph_, 2, 1);
    grid_layout_->addWidget(temp_display_, 1, 0);
    grid_layout_->addWidget(od_display_, 1, 1);
    grid_layout_->addWidget(do_display_, 3, 0);
    grid_layout_->addWidget(ph_display_, 3, 1);
    grid_layout_->addWidget(calibrate_od_button_, 1, 2);
    grid_layout_->addWidget(temperature_slider_, 2, 3, 3, 1);
    grid_layout_->addWidget(temperature_spin_box_, 1, 3);

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
        od_display_->setText(data);
        break;
      case BCommunication::DO:
        do_display_->setText(data);
        break;
      case BCommunication::Temperature:
        temp_display_->setText(data);
        break;
      case BCommunication::Air:

        break;
      case BCommunication::pH:
        ph_display_->setText(data);
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

// Requests the Arduino to zero the OD
void MainWindow::calibrateOD() {
    configure(BCommunication::CalibrateOD);
}

// Sends a desired temperature to the Arduino
void MainWindow::setTemperature(float temperature) {
    configure(BCommunication::SetTemperature);
    port_->write(reinterpret_cast<const char*>(&temperature), sizeof(temperature));
    port_->putChar('\n');
}

// Sends a packet to the Arduino requesting the test cycle to begin for a
// particular chamber
void MainWindow::beginTestCycle(int chamber)
{
    port_->putChar(BCommunication::TestRequest);
    port_->putChar(chamber);
}

void MainWindow::intToDouble(int value) {
    intToDouble((double) value);
}

void MainWindow::doubleToInt(double value) {
    doubleToInt((int) value);
}

void MainWindow::doubleToFloat(double value) {
    doubleToFloat((float) value);
}
