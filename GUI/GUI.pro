######################################################################
# Automatically generated by qmake (3.0) Sun Aug 11 14:44:37 2013
######################################################################

TEMPLATE = app
TARGET = GUI
INCLUDEPATH += .

QT       += core gui serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# Input
HEADERS += Communication.h \
           MainWidget.h \
           Monitor.h \
           qcustomplot.h \
           ui_Control.h \
           ui_MainWidget.h \
           ui_Monitor.h
SOURCES += main.cpp MainWidget.cpp qcustomplot.cpp

RESOURCES = GUI.qrc
