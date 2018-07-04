#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "aboutwindow.h"
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

ShellFunctions shellMW;
ConfigData confDataMW;

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
        //stringstream ss;
        //ss << shellMW.basicCommand << " " << confDataMW.castnowPath << " '" << filePath << "' " << shellMW.extraCommands;
        //string tmp = ss.str();
        //const char* castCommand = tmp.c_str();

        //system(shellMW.stopRunningScreen); //must be here to stop screen session after reopening castnow-gui
        //system(castCommand);
        statusBarCastingMsg();
        shellMW.FileStreamingVAAPI(filePath);
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

void MainWindow::on_castDesktopStartButton_clicked()
{
    shellMW.DesktopStreamingVAAPI();
    ui->castDesktopStartButton->setEnabled(false);
}

void MainWindow::on_castDesktopStopButton_clicked()
{
    ui->statusBar->showMessage("Streaming is stopping. Please wait...");
    shellMW.StopProcessPipe();
    ui->statusBar->showMessage("Streaming stopped");
}

void MainWindow::on_actionOpenFile_triggered()
{
    on_openFileButton_clicked();
}

void MainWindow::on_actionConfig_triggered()
{
    ConfigWindow *configDialog = new ConfigWindow;
    configDialog->show();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutWindow *aboutDialog = new AboutWindow;
    aboutDialog->show();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}
