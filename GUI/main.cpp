#include "MainWidget.h"
#include <QtWidgets/QApplication>
#include <QtCore/QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTimer *timer = new QTimer();
    MainWidget w;
    timer->connect(timer, SIGNAL(timeout()), &w, SLOT(requestData()));
    timer->start(378);
    w.show();

    return a.exec();
}
