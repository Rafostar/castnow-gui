#include "configwindow.h"
#include "ui_configwindow.h"
#include <QPushButton>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

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
    if(confData->castnowPath != "castnow")
    {
        QString castnowPath = QString::fromStdString(confData->castnowPath);
        ui->castnowEditPath->setText(castnowPath);
    }

    if(confData->ffmpegPath != "ffmpeg")
    {
        QString ffmpegPath = QString::fromStdString(confData->ffmpegPath);
        ui->ffmpegEditPath->setText(ffmpegPath);
    }

    ui->doubleSpinBoxFileBitrate->setValue(confData->fileBitrate);
    ui->doubleSpinBoxFileOffset->setValue(confData->fileAudioDelay);

    int VisMode = confData->visualizerMode;
    switch (VisMode)
    {
        case 0 : ui->visDisabledRadioButton->click();
                 break;
        case 1 : ui->visAutoRadioButton->click();
                 break;
        case 2 : ui->visAlwaysRadioButton->click();
                 break;
    }

    ui->spinBoxDesktopFramerate->setValue(confData->desktopFramerate);
    ui->doubleSpinBoxDesktopBitrate->setValue(confData->desktopBitrate);
    ui->doubleSpinBoxDesktopOffset->setValue(confData->desktopAudioDelay);
    ui->spinBoxDesktopQueueSize->setValue(confData->threadQueueSize);
}

void ConfigWindow::UpdateUsedValues()
{
    string castnowEditPathText = ui->castnowEditPath->text().toUtf8().constData();
    string ffmpegEditPathText = ui->ffmpegEditPath->text().toUtf8().constData();

    if(castnowEditPathText != "")
    {
        confData->castnowPath = ui->castnowEditPath->text().toUtf8().constData();
    }
    else
    {
        confData->castnowPath = confData->defaultCastnowPath;
    }

    if(ffmpegEditPathText != "")
    {
        confData->ffmpegPath = ui->ffmpegEditPath->text().toUtf8().constData();
    }
    else
    {
        confData->ffmpegPath = confData->defaultFfmpegPath;
    }

    confData->fileBitrate = ui->doubleSpinBoxFileBitrate->value();
    confData->fileAudioDelay = ui->doubleSpinBoxFileOffset->value();

    if(ui->visDisabledRadioButton->isChecked())
    {
        confData->visualizerMode = 0;
    }
    else if(ui->visAutoRadioButton->isChecked())
    {
        confData->visualizerMode = 1;
    }
    else if(ui->visAlwaysRadioButton->isChecked())
    {
        confData->visualizerMode = 2;
    }

    confData->desktopFramerate = ui->spinBoxDesktopFramerate->value();
    confData->desktopBitrate = ui->doubleSpinBoxDesktopBitrate->value();
    confData->desktopAudioDelay = ui->doubleSpinBoxDesktopOffset->value();
    confData->threadQueueSize = ui->spinBoxDesktopQueueSize->value();
}

void ConfigWindow::RestoreDefaultValues()
{
    ui->doubleSpinBoxFileBitrate->setValue(confData->defaultFileBitrate);
    ui->doubleSpinBoxFileOffset->setValue(confData->defaultFileAudioDelay);

    ui->spinBoxDesktopFramerate->setValue(confData->defaultDesktopFramerate);
    ui->doubleSpinBoxDesktopBitrate->setValue(confData->defaultDesktopBitrate);
    ui->doubleSpinBoxDesktopOffset->setValue(confData->defaultDesktopAudioDelay);
    ui->spinBoxDesktopQueueSize->setValue(confData->defaultThreadQueueSize);
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
        confData->SaveConfigurationToFile();
    }
}
