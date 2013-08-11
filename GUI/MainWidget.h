#ifndef MAINWIDGET_H
#define MAINWIDGET_H

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
    void openSerialPort();
    void closeSerialPort();
    void readData();

private:
    void initActionsConnections();

private:
    Ui::MainWidget *ui;
    QSerialPort *serial;
};

#endif

