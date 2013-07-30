#include "mainwindow.h"


struct SensorData {
    float optical_density;
    float temperature;
    float dissolved_oxygen;
    float ph;
    float airflow;
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initWindow();

    // For now, change this port to whatever the Arduino is connected to
    initPort("/dev/ttyACM0");

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
    lcd_temp_->setTextFormat(Qt::PlainText);
    lcd_od_ = new QLabel("0");
    lcd_do_ = new QLabel("0");
    lcd_ph_ = new QLabel("0");
    temp_ = new QLabel("Temperature");
    od_ = new QLabel("OD");
    do_ = new QLabel("DO");
    ph_ = new QLabel("pH");
    grid_layout_ = new QGridLayout();
    overview_ = new QGroupBox(this);
    grid_layout_->addWidget(temp_, 0, 0);
    grid_layout_->addWidget(od_, 0, 1);
    grid_layout_->addWidget(do_, 2, 0);
    grid_layout_->addWidget(ph_, 2, 1);
    grid_layout_->addWidget(lcd_temp_, 1, 0);
    grid_layout_->addWidget(lcd_od_, 1, 1);
    grid_layout_->addWidget(lcd_do_, 3, 0);
    grid_layout_->addWidget(lcd_ph_, 3, 1);
    overview_->setLayout(grid_layout_);
    setCentralWidget(overview_);
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

// Called when data is available to be read from the Arduino
void MainWindow::readData()
{
    int length;
    QString data;

    length = port_->read(1).toInt();
    data = port_->read(length);
    lcd_temp_->setText(data);
}

// Sends a packet to the Arduino requesting a reading from all sensors
void MainWindow::requestData()
{
    port_->write("1");
    port_->waitForReadyRead(0);
}

// Overloaded function. Requests data of a particular type
void MainWindow::requestData(PacketType packet_type)
{

}

// Sends a packet to the Arduino requesting the test cycle to begin for a
// particular chamber
void MainWindow::beginTestCycle(int chamber)
{

}
