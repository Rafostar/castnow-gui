#include "configwindow.h"
#include "ui_configwindow.h"
#include "configdata.h"
#include <QPushButton>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

ConfigData confDataCW;

QString framerateInfoText = "Sets the number of frames, that are displayed in one second of video.\n"
                            "Raising this value increases playback smoothness.\n"
                            "Lower the value if you have weak CPU.";

QString bitrateInfoText = "Sets the video bitrate limit.\n"
                          "Raising this value increases video quality.\n"
                          "Lower the value if you are experiencing lags.";

QString audioOffsetText = "Sets the audio time offset relative to video.\n"
                          "Can be either positive or negative value.\n"
                          "Positive offset means that the audio stream will be delayed by duration specified.";

QString queueSizeInfoText = "Sets the maximum number of queued packets when reading from the file or device.\n"
                            "Packets may be discarded if they are not read in a timely manner.\n"
                            "Raising this value can avoid it.";

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    confDataCW.ProcessConfigFile();
    ui->setupUi(this);

    UpdateConfigWindowValues();

    ui->spinBoxDesktopFramerate->setToolTip(framerateInfoText);
    ui->doubleSpinBoxDesktopBitrate->setToolTip(bitrateInfoText);
    ui->doubleSpinBoxDesktopOffset->setToolTip(audioOffsetText);
    ui->spinBoxDesktopQueueSize->setToolTip(queueSizeInfoText);


}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::on_doubleSpinBoxFileOffset_valueChanged(const QString &arg1)
{
    if(arg1 == "-0.000 sec")
    {
        ui->doubleSpinBoxFileOffset->setValue(0.000);
    }
}

void ConfigWindow::on_doubleSpinBoxOffset_valueChanged(const QString &arg1)
{
    if(arg1 == "-0.000 sec")
    {
        ui->doubleSpinBoxDesktopOffset->setValue(0.000);
    }
}

void ConfigWindow::UpdateConfigWindowValues()
{
    if(confDataCW.castnowPath != "castnow")
    {
        QString castnowPath = QString::fromStdString(confDataCW.castnowPath);
        ui->castnowEditPath->setText(castnowPath);
    }

    if(confDataCW.ffmpegPath != "ffmpeg")
    {
        QString ffmpegPath = QString::fromStdString(confDataCW.ffmpegPath);
        ui->ffmpegEditPath->setText(ffmpegPath);
    }

    ui->spinBoxDesktopFramerate->setValue(confDataCW.desktopFramerate);
    ui->doubleSpinBoxDesktopBitrate->setValue(confDataCW.desktopBitrate);
    ui->doubleSpinBoxDesktopOffset->setValue(confDataCW.desktopAudioDelay);
    ui->spinBoxDesktopQueueSize->setValue(confDataCW.threadQueueSize);
}

void ConfigWindow::UpdateUsedValues()
{
    string castnowEditPathText = ui->castnowEditPath->text().toUtf8().constData();
    string ffmpegEditPathText = ui->ffmpegEditPath->text().toUtf8().constData();

    if(castnowEditPathText != "")
    {
        confDataCW.castnowPath = ui->castnowEditPath->text().toUtf8().constData();
    }
    else
    {
        confDataCW.castnowPath = confDataCW.defaultCastnowPath;
    }

    if(ffmpegEditPathText != "")
    {
        confDataCW.ffmpegPath = ui->ffmpegEditPath->text().toUtf8().constData();
    }
    else
    {
        confDataCW.ffmpegPath = confDataCW.defaultFfmpegPath;
    }

    confDataCW.desktopFramerate = ui->spinBoxDesktopFramerate->value();
    confDataCW.desktopBitrate = ui->doubleSpinBoxDesktopBitrate->value();
    confDataCW.desktopAudioDelay = ui->doubleSpinBoxDesktopOffset->value();
    confDataCW.threadQueueSize = ui->spinBoxDesktopQueueSize->value();
}

void ConfigWindow::on_buttonBoxConfig_clicked(QAbstractButton *button)
{
    if((QPushButton *)button == ui->buttonBoxConfig->button(QDialogButtonBox::RestoreDefaults))
    {
        ui->spinBoxDesktopFramerate->setValue(confDataCW.defaultDesktopFramerate);
        ui->doubleSpinBoxDesktopBitrate->setValue(confDataCW.defaultDesktopBitrate);
        ui->doubleSpinBoxDesktopOffset->setValue(confDataCW.defaultDesktopAudioDelay);
        ui->spinBoxDesktopQueueSize->setValue(confDataCW.defaultThreadQueueSize);
    }
    else if((QPushButton *)button == ui->buttonBoxConfig->button(QDialogButtonBox::Save))
    {
        UpdateUsedValues();
        confDataCW.SaveConfigurationToFile();
    }
}
