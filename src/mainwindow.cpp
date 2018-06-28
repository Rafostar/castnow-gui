#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDesktopWidget>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

QString filePathQS;
string filePath;
QString openFileName;
QString message;

ShellFunctions shell;

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

int MainWindow::checkFilePath()
{
    filePathQS = ui->insertFilePath->text();
    filePath = filePathQS.toUtf8().constData();

    if(filePath == "")
    {
        return 1;
    }
    else
    {
        // MISSING CHECKING IF FILE EXISTS
        return 0;
    }
}

void MainWindow::statusBarCastingMsg()
{
    string baseFilename = filePath.substr(filePath.find_last_of("/\\") + 1);
    QString baseFilenameQS = QString::fromStdString(baseFilename);
    message = QString("Casting: %1").arg(baseFilenameQS);
    ui->statusBar->showMessage(message);
}

void MainWindow::statusBarError()
{
    ui->statusBar->showMessage("Empty path to file!");
}

void MainWindow::on_streamButton_clicked()
{
    if(checkFilePath() == 0)
    {
        stringstream ss;
        ss << shell.basicCommand << " " << shell.castnowPath << " '" << filePath << "' " << shell.extraCommands;
        string tmp = ss.str();
        const char* castCommand = tmp.c_str();

        system(shell.stopRunningScreen); //must be here to stop screen session after reopening castnow-gui
        system(castCommand);
        statusBarCastingMsg();
    }
    else
    {
        statusBarError();
    }
}

void MainWindow::on_openFileButton_clicked()
{
    QString defaultPath = "/home/";
    defaultPath += getlogin();
    defaultPath += "/Videos/";

    openFileName = QFileDialog::getOpenFileName(this, tr("Open File"), defaultPath, tr("Media Files (*.mp3 *.mp4 *.mkv *.avi)"));
    if(openFileName!="")
    {
        ui->insertFilePath->setText(openFileName);
    }
}

void MainWindow::on_castDesktopButton_clicked()
{
    shell.DesktopStreamingVAAPI(1600,900,30,32,0,4.5);
}
