#include "configwindow.h"
#include "ui_configwindow.h"
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

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    ui->spinBoxFramerate->setToolTip(framerateInfoText);
    ui->doubleSpinBoxBitrate->setToolTip(bitrateInfoText);
    ui->doubleSpinBoxOffset->setToolTip(audioOffsetText);
    ui->spinBoxQueueSize->setToolTip(queueSizeInfoText);
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::on_doubleSpinBoxOffset_valueChanged(const QString &arg1)
{
    if(arg1 == "-0.000 sec")
    {
        ui->doubleSpinBoxOffset->setValue(0.000);
    }
}
