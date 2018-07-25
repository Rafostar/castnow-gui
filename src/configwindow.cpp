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

QString visualizerAutoInfoText = "Shows music visualizer only when cd art is not available.";

QString visualizerAlwaysInfoText = "Always shows music visualizer.";

QString visualizerDisabledInfoText = "Never shows music visualizer (lower cpu usage).";

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    ui->doubleSpinBoxFileBitrate->setToolTip(bitrateInfoText);
    ui->doubleSpinBoxFileOffset->setToolTip(audioOffsetText);

    ui->spinBoxDesktopFramerate->setToolTip(framerateInfoText);
    ui->doubleSpinBoxDesktopBitrate->setToolTip(bitrateInfoText);
    ui->doubleSpinBoxDesktopOffset->setToolTip(audioOffsetText);
    ui->spinBoxDesktopQueueSize->setToolTip(queueSizeInfoText);

    ui->visAutoRadioButton->setToolTip(visualizerAutoInfoText);
    ui->visAlwaysRadioButton->setToolTip(visualizerAlwaysInfoText);
    ui->visDisabledRadioButton->setToolTip(visualizerDisabledInfoText);
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

void ConfigWindow::on_doubleSpinBoxDesktopOffset_valueChanged(const QString &arg1)
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

    ui->doubleSpinBoxFileBitrate->setValue(confDataCW.fileBitrate);
    ui->doubleSpinBoxFileOffset->setValue(confDataCW.fileAudioDelay);

    int VisMode = confDataCW.visualizerMode;
    switch (VisMode)
    {
        case 0 : ui->visDisabledRadioButton->click();
                 break;
        case 1 : ui->visAutoRadioButton->click();
                 break;
        case 2 : ui->visAlwaysRadioButton->click();
                 break;
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

    confDataCW.fileBitrate = ui->doubleSpinBoxFileBitrate->value();
    confDataCW.fileAudioDelay = ui->doubleSpinBoxFileOffset->value();

    if(ui->visDisabledRadioButton->isChecked())
    {
        confDataCW.visualizerMode = 0;
    }
    else if(ui->visAutoRadioButton->isChecked())
    {
        confDataCW.visualizerMode = 1;
    }
    else if(ui->visAlwaysRadioButton->isChecked())
    {
        confDataCW.visualizerMode = 2;
    }

    confDataCW.desktopFramerate = ui->spinBoxDesktopFramerate->value();
    confDataCW.desktopBitrate = ui->doubleSpinBoxDesktopBitrate->value();
    confDataCW.desktopAudioDelay = ui->doubleSpinBoxDesktopOffset->value();
    confDataCW.threadQueueSize = ui->spinBoxDesktopQueueSize->value();
}

void ConfigWindow::RestoreDefaultValues()
{
    ui->doubleSpinBoxFileBitrate->setValue(confDataCW.defaultFileBitrate);
    ui->doubleSpinBoxFileOffset->setValue(confDataCW.defaultFileAudioDelay);

    ui->spinBoxDesktopFramerate->setValue(confDataCW.defaultDesktopFramerate);
    ui->doubleSpinBoxDesktopBitrate->setValue(confDataCW.defaultDesktopBitrate);
    ui->doubleSpinBoxDesktopOffset->setValue(confDataCW.defaultDesktopAudioDelay);
    ui->spinBoxDesktopQueueSize->setValue(confDataCW.defaultThreadQueueSize);
}

void ConfigWindow::on_buttonBoxConfig_clicked(QAbstractButton *button)
{
    if((QPushButton *)button == ui->buttonBoxConfig->button(QDialogButtonBox::RestoreDefaults))
    {
        RestoreDefaultValues();
    }
    else if((QPushButton *)button == ui->buttonBoxConfig->button(QDialogButtonBox::Save))
    {
        UpdateUsedValues();
        confDataCW.SaveConfigurationToFile();
    }
}
