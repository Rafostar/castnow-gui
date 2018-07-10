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

qint64 mediaLenght;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mediaPlayer->setVideoOutput(ui->videoWidget);
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::PreviewStatusChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::ChangePreviewProgress);

    //FIXES: QWidget::paintEngine: Should no longer be called
    mediaPlayer->setMedia(QUrl("qrc:/player_bugfix/videos/av_no_media_short.mp4"));
    mediaPlayer->play();
    //mediaPlayer->stop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::CheckFilePath(string type)
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
    ui->castDesktopButton->setEnabled(state);
    ui->avStopButton->setEnabled(!state);
}

void MainWindow::StatusBarCastingMsg()
{
    string baseFilename = filePath.substr(filePath.find_last_of("/\\") + 1);
    QString baseFilenameQS = QString::fromStdString(baseFilename);
    message = QString("Casting: %1").arg(baseFilenameQS);
    ui->statusBar->showMessage(message);
}

void MainWindow::SetMediaPreview(string mediaType, QString path = "none")
{
    QPalette palette = ui->videoWidget->palette();

    if(mediaType == "video")
    {
        //mediaPlayer->setVideoOutput(ui->videoWidget);
        mediaPlayer->setMedia(QUrl::fromLocalFile(path));
        mediaPlayer->play();
    }
    else if(mediaType == "picture")
    {
        palette.setBrush(QPalette::Window, QBrush(QPixmap(path)));
        ui->videoWidget->setAutoFillBackground(true);
        ui->videoWidget->setPalette(palette);
        ui->videoWidget->show();
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

void MainWindow::PreviewStatusChanged()
{
    int mediaStatus = mediaPlayer->mediaStatus();

    switch(mediaStatus)
    {
        case 3: mediaLenght = round(mediaPlayer->duration() / 1000);
                ui->avProgressBar->setMaximum(mediaLenght);
                ui->avProgressBar->setValue(0);
                break;
        case 7: ui->avProgressBar->setFormat("00:00:00");
                ui->avProgressBar->setValue(0);
                mediaPlayer->setMedia(QUrl("qrc:/player_previews/videos/av_no_media.mp4"));
                //mediaPlayer->play();
                break;
        case 8: cout << "Cannot Play This Media!"; //Needs better error handling
                break;
    }
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
    if(CheckFilePath("file") == 0)
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
    if(CheckFilePath("link") == 0)
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

void MainWindow::on_castDesktopButton_clicked()
{
    EnableCastingButtons(false);
    ui->statusBar->showMessage("Started casting desktop");
    shellMW.DesktopStreamingVAAPI();
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

void MainWindow::on_castCameraButton_clicked()
{

}

void MainWindow::on_castCDButton_clicked()
{
    //mediaPlayer->setVideoOutput(ui->videoWidget); //Interupts photo preview

    //SetMediaPreview("video", "/path/to/file.mp4");
}
