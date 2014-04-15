#-------------------------------------------------
#
# Project created by QtCreator 2014-04-14T03:52:25
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bearcat-remote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    bearcat.cpp

HEADERS  += mainwindow.h \
    bearcat.h

FORMS    += mainwindow.ui
