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
        stringstream ss;
        ss << shellMW.basicCommand << " " << confDataMW.castnowPath << " '" << filePath << "' " << shellMW.extraCommands;
        string tmp = ss.str();
        const char* castCommand = tmp.c_str();

        system(shellMW.stopRunningScreen); //must be here to stop screen session after reopening castnow-gui
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
    int desktopWidth = confDataMW.desktopWidth;
    int desktopHeight = confDataMW.desktopHeight;
    int desktopFramerate = confDataMW.desktopFramerate;
    int threadQueueSize = confDataMW.threadQueueSize;
    double desktopAudioDelay = confDataMW.desktopAudioDelay;
    double desktopBitrate = confDataMW.desktopBitrate;

    shellMW.DesktopStreamingVAAPI(desktopWidth,desktopHeight,desktopFramerate,threadQueueSize,desktopAudioDelay,desktopBitrate);
}

void MainWindow::on_actionConfig_triggered()
{
    ConfigWindow *configDialog = new ConfigWindow;
    configDialog->show();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutWindow *aboutDialog = new AboutWindow;
    aboutDialog->show();
}
