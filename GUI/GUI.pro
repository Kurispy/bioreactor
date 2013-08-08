QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    OD.cpp

HEADERS  += mainwindow.h \
    Communication.h \
    OD.h

OTHER_FILES += \
    README.txt
