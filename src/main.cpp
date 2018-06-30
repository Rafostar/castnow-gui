#include "mainwindow.h"
#include <QApplication>
//#include <QTimer>
#include <QDesktopWidget>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ConfigData confData;
    QDesktopWidget *desktop = QApplication::desktop();

    confData.desktopWidth = desktop->width();
    confData.desktopHeight = desktop->height();

    int middleWidth = (confData.desktopWidth - w.width())/2;
    int middleHeight = (confData.desktopHeight - w.height()-50)/2;

    confData.ProcessConfigFile();

    w.move(middleWidth,middleHeight);
    w.show();

    return a.exec();
}
