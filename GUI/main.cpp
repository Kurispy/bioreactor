#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer *timer = new QTimer();
    MainWindow w;
    timer->connect(timer, SIGNAL(timeout()), &w, SLOT(requestData()));
    timer->start(1000);
    w.show();
    
    return a.exec();
}
