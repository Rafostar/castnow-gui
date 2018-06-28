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

QString FilePathQS;
string FilePath;
QString OpenFileName;
QString Message;

shellfunctions shell;

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
    FilePathQS = ui->insertFilePath->text();
    FilePath = FilePathQS.toUtf8().constData();

    if(FilePath == "")
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
    string BaseFilename = FilePath.substr(FilePath.find_last_of("/\\") + 1);
    QString BaseFilenameQS = QString::fromStdString(BaseFilename);
    Message = QString("Casting: %1").arg(BaseFilenameQS);
    ui->statusBar->showMessage(Message);
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
        ss << shell.BasicCommand << " '" << FilePath << "' " << shell.ExtraCommands;
        string tmp = ss.str();
        const char* CastCommand = tmp.c_str();

        system(shell.StopRunningScreen); //must be here to stop screen session after reopening castnow-gui
        system(CastCommand);
        statusBarCastingMsg();
    }
    else
    {
        statusBarError();
    }
}

void MainWindow::on_openFileButton_clicked()
{
    QString DefaultPath = "/home/";
    DefaultPath += getlogin();
    DefaultPath += "/Videos/";

    OpenFileName = QFileDialog::getOpenFileName(this, tr("Open File"), DefaultPath, tr("Media Files (*.mp3 *.mp4 *.mkv *.avi)"));
    ui->insertFilePath->setText(OpenFileName);
}

void MainWindow::on_castDesktopButton_clicked()
{
    shell.DesktopStreamingVAAPI(1600,900,30,0,4.5);
}
