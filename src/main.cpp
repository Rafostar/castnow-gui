#include "mainwindow.h"
#include <QApplication>
#include <QApplication>
#include <QTimer>
#include <QDesktopWidget>
#include <string>
#include <sstream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    shellfunctions shell;
    QDesktopWidget *desktop = QApplication::desktop();

    shell.desktopWidth = desktop->width();
    shell.desktopHeight = desktop->height();

    int middleWidth = (shell.desktopWidth - w.width())/2;
    int middleHeight = (shell.desktopHeight - w.height()-50)/2;

    w.move(middleWidth,middleHeight);
    w.show();

    return a.exec();
}
