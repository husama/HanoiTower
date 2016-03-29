#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T16:33:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hanoiTower
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hanoipanel.cpp \
    diskstack.cpp \
    disk.cpp \
    showstack.cpp

HEADERS  += mainwindow.h \
    hanoipanel.h \
    diskstack.h \
    disk.h \
    showstack.h

FORMS    += mainwindow.ui

RESOURCES +=

RC_FILE = myapp.rc
