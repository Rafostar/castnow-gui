#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_streamButton_clicked()
{
    string CastFile="This File";
    stringstream ss;
    ss << "echo " << CastFile;
    string tmp = ss.str();
    const char* CastCommand = tmp.c_str();
    system(CastCommand);
}
