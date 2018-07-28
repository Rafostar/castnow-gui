#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDesktopWidget>
#include <QVideoWidget>
#include <QFileSystemWatcher>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

QString filePathQS;
string filePath;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(fileWatch, &QFileSystemWatcher::fileChanged, this, &MainWindow::LogFileChanged);
    ofstream logFile(confData->castnowLogFile.fileName().toStdString());
    logFile.close();
    fileWatch->addPath(confData->castnowLogFile.fileName());

    connect(mediaPlayer, &QMediaPlayer::mediaChanged, this, &MainWindow::PreviewMediaChanged);
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::PreviewStatusChanged);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, &MainWindow::ChangePreviewProgress);

    mediaPlayer->setVideoOutput(ui->videoWidget);
    ui->videoWidget->hide();
}

MainWindow::~MainWindow()
{
    if(ui->castFileButton->isEnabled() == false)
    {
        shellFcn->StopProcessPipe();
    }

    delete ui;
    confData->castnowLogFile.remove();
}


// ### MAIN WINDOW FUNCTIONS ### //

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

void MainWindow::DisplayMessage(QString messageType, QString messageText)
{
    int posX = this->pos().x() + ((this->width() - msgWin->width()) / 2);
    int posY = this->pos().y() + ((this->height() - msgWin->height() / 2) / 2);
    msgWin->move(posX, posY);
    msgWin->EditMessage(messageType, messageText);
}


// ### MAIN WINDOWS BUTTONS ACTIONS ### //

void MainWindow::on_openFileButton_clicked()
{
    QString defaultPath = "/home/";
    defaultPath += getlogin();
    defaultPath += "/Videos/";

    QString openFileName = QFileDialog::getOpenFileName(this, tr("Open File"), defaultPath, tr("Media Files (*.mp3 *.mp4 *.mkv *.avi)"));
    if(openFileName!="")
    {
        ui->insertFilePath->setText(openFileName);
    }
}

void MainWindow::on_castFileButton_clicked()
{
    if(CheckPath("file") == 0)
    {
        EnableCastingButtons(false);
        shellFcn->FileStreamingVAAPI(filePath);
    }
    else
    {
        DisplayMessage("Error","Empty file path field!");
    }
}

void MainWindow::on_castLinkButton_clicked()
{
    if(CheckPath("link") == 0)
    {
        EnableCastingButtons(false);
        shellFcn->LinkStreaming(filePath);
    }
    else
    {
        DisplayMessage("Error","Empty link field!");
    }
}


// ### MENU BAR ACTIONS ### //

void MainWindow::on_actionOpenFile_triggered()
{
    on_openFileButton_clicked();
}

void MainWindow::on_actionConfig_triggered()
{
    ConfigWindow *confWin = new ConfigWindow;

    confData->ProcessConfigFile();
    confWin->UpdateConfigWindowValues();
    confWin->show();
}

void MainWindow::on_actionAbout_triggered()
{
    aboutWin->show();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}


// ### BOTTOM BUTTONS ACTIONS ### //

void MainWindow::on_castCDButton_clicked()
{
    // temporary for player testing:
    //SetMediaPreview("video", "/tmp/test.mp4");

    EnableCastingButtons(false);
    shellFcn->MusicVisualizerStreaming("/tmp/test.flac");
}

void MainWindow::on_castDesktopButton_clicked()
{
    EnableCastingButtons(false);
    ui->avProgressBar->setFormat("Started casting desktop");
    shellFcn->DesktopStreamingVAAPI();
}

void MainWindow::on_castFolderButton_clicked()
{
    DisplayMessage("Error1", "string messageText");
}

void MainWindow::on_castDeviceButton_clicked()
{
    shellFcn->CaptureDeviceStreaming();
}


// ### LOG FILE HANDLING ### //

void MainWindow::LogFileChanged()
{
    string lineContent = LogFileContent();

    if(lineContent == prevLineContent) return;

    prevLineContent = lineContent;

    if(lineContent == "Scanning")
    {
        ui->avProgressBar->setFormat("Loading...");
    }
    else if(lineContent == "Error")
    {
        on_avStopButton_clicked();
    }
}

string MainWindow::LogFileContent()
{
    QFile readFile(confData->castnowLogFile.fileName());
    readFile.open(QIODevice::ReadOnly | QIODevice::Text);

    int prevLogFileSize = logFileSize;
    logFileSize = readFile.size();
    int logFileDiff = logFileSize - prevLogFileSize;

    readFile.seek(logFileSize - logFileDiff);

    string lineContent = readFile.readLine(logFileDiff).toStdString();
    readFile.close();

    return lineContent;
}


// ### MEDIA PLAYER BUTTONS ACTIONS ### //

void MainWindow::on_avStopButton_clicked()
{
    ui->avProgressBar->setFormat("Streaming is stopping. Please wait...");
    shellFcn->StopProcessPipe();
    EnableCastingButtons(true);
    ui->avProgressBar->setFormat("00:00:00");
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


// ### MEDIA PLAYER RELATED FUNCTIONS ### //

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
