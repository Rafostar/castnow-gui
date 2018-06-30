#include "aboutwindow.h"
#include "ui_aboutwindow.h"
#include <QDesktopServices>

AboutWindow::AboutWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutWindow)
{
    ui->setupUi(this);
}

AboutWindow::~AboutWindow()
{
    delete ui;
}
