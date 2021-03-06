#-------------------------------------------------
#
# Project created by QtCreator 2018-06-27T12:24:01
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = castnow-gui
TEMPLATE = app

target.path = /usr/local/bin
INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp \
    shellfunctions.cpp \
    configwindow.cpp \
    configdata.cpp \
    aboutwindow.cpp \
    messagewindow.cpp \
    visualizerconfig.cpp

HEADERS  += mainwindow.h \
    shellfunctions.h \
    configwindow.h \
    configdata.h \
    aboutwindow.h \
    messagewindow.h \
    visualizerconfig.h

FORMS    += mainwindow.ui \
    configwindow.ui \
    aboutwindow.ui \
    messagewindow.ui

RESOURCES += \
    resources.qrc
