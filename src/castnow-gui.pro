#-------------------------------------------------
#
# Project created by QtCreator 2018-06-27T12:24:01
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = castnow-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    shellfunctions.cpp

HEADERS  += mainwindow.h \
    shellfunctions.h

FORMS    += mainwindow.ui
