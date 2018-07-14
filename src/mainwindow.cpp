#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configwindow.h"
#include "aboutwindow.h"
#include <QFileDialog>
#include <QDesktopWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

ShellFunctions shellMW;
ConfigData confDataMW;

QString filePathQS;
string filePath;
QString openFileName;
QString message;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(mediaPlayer, &QMediaPlayer::mediaChanged, this, &MainWindow::PreviewMediaChanged);
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::PreviewStatusChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::ChangePreviewProgress);

    mediaPlayer->setVideoOutput(ui->videoWidget);
    ui->videoWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::CheckPath(string type)
{
    if(type == "file")
    {
        filePathQS = ui->insertFilePath->text();
        filePath = filePathQS.toUtf8().constData();
    }
    else if(type == "link")
    {
        filePathQS = ui->insertLink->text();
        filePath = filePathQS.toUtf8().constData();
    }
    else
    {
        return 1;
    }

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

void MainWindow::EnableCastingButtons(bool state)
{
    ui->castFileButton->setEnabled(state);
    ui->castLinkButton->setEnabled(state);

    ui->castCDButton->setEnabled(state);
    ui->castDesktopButton->setEnabled(state);
    ui->castFolderButton->setEnabled(state);
    ui->castDeviceButton->setEnabled(state);

    ui->avToggleButton->setEnabled(!state);
    ui->avStopButton->setEnabled(!state);
    ui->avNextButton->setEnabled(!state);
    ui->avPreviousButton->setEnabled(!state);
}

void MainWindow::StatusBarCastingMsg()
{
    string baseFilename = filePath.substr(filePath.find_last_of("/\\") + 1);
    QString baseFilenameQS = QString::fromStdString(baseFilename);
    message = QString("Casting: %1").arg(baseFilenameQS);
    ui->statusBar->showMessage(message);
}



void MainWindow::StatusBarFileError()
{
    ui->statusBar->showMessage("Empty file path field!");
}

void MainWindow::StatusBarLinkError()
{
    ui->statusBar->showMessage("Empty link field!");
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

void MainWindow::on_castFileButton_clicked()
{
    if(CheckPath("file") == 0)
    {
        //system(shellMW.stopRunningScreen); //must be here to stop screen session after reopening castnow-gui

        EnableCastingButtons(false);
        StatusBarCastingMsg();
        shellMW.FileStreamingVAAPI(filePath);
    }
    else
    {
        StatusBarFileError();
    }
}

void MainWindow::on_castLinkButton_clicked()
{
    if(CheckPath("link") == 0)
    {
        //system(shellMW.stopRunningScreen); //must be here to stop screen session after reopening castnow-gui

        EnableCastingButtons(false);
        StatusBarCastingMsg();
        shellMW.LinkStreaming(filePath);
    }
    else
    {
        StatusBarLinkError();
    }
}

void MainWindow::on_avStopButton_clicked()
{
    ui->statusBar->showMessage("Streaming is stopping. Please wait...");
    shellMW.StopProcessPipe();
    EnableCastingButtons(true);
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


// ### BOTTOM BUTTONS ACTIONS ### //

void MainWindow::on_castCDButton_clicked()
{
    // temporary for player testing:
    SetMediaPreview("video", "/tmp/test.mp4");
}

void MainWindow::on_castDesktopButton_clicked()
{
    EnableCastingButtons(false);
    ui->statusBar->showMessage("Started casting desktop");
    shellMW.DesktopStreamingVAAPI();
}

void MainWindow::on_castFolderButton_clicked()
{

}

void MainWindow::on_castDeviceButton_clicked()
{
    shellMW.CaptureDeviceStreaming();
}


// ### Media Player Related Functions ### //

void MainWindow::SetMediaPreview(string mediaType, QString path = "none")
{
    if(mediaType == "video")
    {
        mediaPlayer->setMedia(QUrl::fromLocalFile(path));
        mediaPlayer->play();
    }
    else if(mediaType == "picture")
    {

    }
    else if(mediaType == "audio")
    {

    }
    else if(mediaType == "link")
    {

    }
    else if(mediaType == "cd")
    {

    }
    else if(mediaType == "desktop")
    {

    }
    else if(mediaType == "device")
    {

    }
}

void MainWindow::PreviewMediaChanged()
{
    //TO DO: CHECK FILETYPE AND SET VIDEO/IMAGE HERE

    /* LOADING MEDIA:
     double mediaLenght = -1;
     ui->avProgressBar->setMaximum(mediaLenght);
    */

}

void MainWindow::PreviewStatusChanged()
{
    int mediaStatus = mediaPlayer->mediaStatus();
    double mediaLenght;

    switch(mediaStatus)
    {
        case 5:
        case 6: mediaLenght = mediaPlayer->duration();
                mediaLenght = round(mediaLenght / 1000);
                ui->avProgressBar->setMaximum(mediaLenght);
                ui->avProgressBar->setValue(0);
                ui->videoFrame->setAutoFillBackground(false);
                ui->videoWidget->show();
                break;
        case 7: ui->avProgressBar->setFormat("00:00:00");
                ui->avProgressBar->setMaximum(1);
                ui->avProgressBar->setValue(0);
                ui->videoFrame->setStyleSheet("border : 2px solid;");
                ChangePreviewImage(":/player_previews/images/av_no_media.png");
                break;
        case 8: cout << "Cannot Play This Media!"; //Needs better error handling
                break;
    }
}

void MainWindow::ChangePreviewImage(const char *imgResource)
{
    QPalette palette = ui->videoFrame->palette();
    palette.setBrush(QPalette::Window, QBrush(QPixmap(imgResource)));
    ui->videoFrame->setPalette(palette);
    ui->videoFrame->setAutoFillBackground(true);
    ui->videoWidget->hide();
}

QString MainWindow::ConvertProgressTime(double mediaPosition)
{
  int sec, min, hrs;
  hrs = mediaPosition / 3600;
  min = mediaPosition / 60 - (hrs * 60);
  sec = mediaPosition - (hrs * 3600) - (min * 60);

  ostringstream progressTime;
  progressTime << setfill('0') << setw(2) << hrs << ":" << setw(2) << min << ":" << setw(2) << sec;
  QString progressTimeQS = QString::fromStdString(progressTime.str());
  return progressTimeQS;
}

void MainWindow::ChangePreviewProgress()
{

    double mediaPosition = mediaPlayer->position();
    mediaPosition = round(mediaPosition / 1000);

    ui->avProgressBar->setFormat(ConvertProgressTime(mediaPosition));
    ui->avProgressBar->setValue(mediaPosition);
}

void MainWindow::on_avToggleButton_clicked()
{
    int playingState = mediaPlayer->state();

    if(playingState == 1)
    {
        mediaPlayer->pause();
        ui->avToggleButton->setStyleSheet("background-color: rgb(138, 226, 52);");
        ui->avToggleButton->setIcon(QIcon(":/player_controls/images/av_play.png"));
    }
    else if(playingState == 2)
    {
        mediaPlayer->play();
        ui->avToggleButton->setStyleSheet("background-color: rgb(252, 233, 79);");
        ui->avToggleButton->setIcon(QIcon(":/player_controls/images/av_pause.png"));
    }
}
