#-------------------------------------------------
#
# Project created by QtCreator 2013-07-23T12:37:32
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Communication.h

OTHER_FILES += \
    README.txt
