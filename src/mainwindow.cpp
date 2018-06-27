#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
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

//---Commands---//
string BasicCommand="screen -d -m -S cast_session castnow";
string ExtraCommands="";
const char* StopRunningScreen="screen -S cast_session -X stuff ^C > /dev/null"; //prevent running castnow more than once


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
        ss << BasicCommand << " '" << FilePath << "' " << ExtraCommands;
        string tmp = ss.str();
        const char* CastCommand = tmp.c_str();

        system(StopRunningScreen); //must be here to stop screen session after reopening castnow-gui
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
