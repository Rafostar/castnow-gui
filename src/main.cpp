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
    QDesktopWidget *desktop = QApplication::desktop();

    int srodekSzerEkranu;
    int srodekWysEkranu;

    srodekSzerEkranu = (desktop->width() - w.width())/2;
    srodekWysEkranu = (desktop->height() - w.height()-50)/2;

    w.move(srodekSzerEkranu,srodekWysEkranu);
    w.show();

    return a.exec();
}
