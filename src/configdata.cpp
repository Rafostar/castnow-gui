#include "configdata.h"
#include "configwindow.h"
#include <QDesktopWidget>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

string configFilePath;

string ConfigData::castnowLogCommand = "| grep --line-buffered -Eo '[A-Z][a-z]{1,10}' | grep --line-buffered -v 'State' > ";
QFile ConfigData::castnowLogFile("/tmp/castnow.log");

// ### DEFAULT VALUES ### //
string ConfigData::defaultCastnowPath = "castnow";
string ConfigData::defaultFfmpegPath = "ffmpeg";

double ConfigData::defaultFileBitrate = 4;
double ConfigData::defaultFileAudioDelay = 0;
int ConfigData::defaultVisualizerMode = 1;

int ConfigData::defaultDesktopFramerate = 30;
double ConfigData::defaultDesktopBitrate = 4;
double ConfigData::defaultDesktopAudioDelay = 0;
int ConfigData::defaultThreadQueueSize = 128;

// ### CURRENT VALUES STORAGE ### //
int ConfigData::desktopWidth;
int ConfigData::desktopHeight;

string ConfigData::castnowPath = ConfigData::defaultCastnowPath;
string ConfigData::ffmpegPath = ConfigData::defaultFfmpegPath;

double ConfigData::fileBitrate = ConfigData::defaultFileBitrate;
double ConfigData::fileAudioDelay = ConfigData::defaultFileAudioDelay;
int ConfigData::visualizerMode = ConfigData::defaultVisualizerMode;

int ConfigData::desktopFramerate = ConfigData::defaultDesktopFramerate;
double ConfigData::desktopBitrate = ConfigData::defaultDesktopBitrate;
double ConfigData::desktopAudioDelay = ConfigData::defaultDesktopAudioDelay;
int ConfigData::threadQueueSize = ConfigData::defaultThreadQueueSize;

bool ConfigData::CheckConfigFile()
{
    configFilePath = "/home/";
    configFilePath += getlogin();
    configFilePath += "/.config/castnow-gui/castnow-gui.cfg";

    ifstream configFile(configFilePath);
    configFile.close();
    return (bool)configFile;
}

void ConfigData::ReadConfigFile()
{
    setlocale(LC_NUMERIC, "C");

    ifstream configFile;
    string configLine;
    configFile.open(configFilePath);

    while(getline(configFile, configLine))
    {
        istringstream currentLine(configLine);
        string configParamName;

        if(getline(currentLine, configParamName, '='))
        {
            string configParamValue;
            if(getline(currentLine, configParamValue))
            {
                if(configParamName == "castnowPath") castnowPath = configParamValue;
                else if(configParamName == "ffmpegPath") ffmpegPath = configParamValue;
                else if(configParamName == "fileBitrate") fileBitrate = stod(configParamValue);
                else if(configParamName == "fileAudioDelay") fileAudioDelay = stod(configParamValue);
                else if(configParamName == "visualizerMode") visualizerMode = stoi(configParamValue);
                else if(configParamName == "desktopFramerate") desktopFramerate = stoi(configParamValue);
                else if(configParamName == "desktopBitrate") desktopBitrate = stod(configParamValue);
                else if(configParamName == "desktopAudioDelay") desktopAudioDelay = stod(configParamValue);
                else if(configParamName == "threadQueueSize") threadQueueSize = stoi(configParamValue);
            }
        }
    }
    configFile.close();
}

void ConfigData::CreateDefaultConfigFile()
{
    const char* createConfigDir = "mkdir -p ~/.config/castnow-gui";
    system(createConfigDir);
    ofstream configFile(configFilePath);
    configFile << "castnowPath=" << defaultCastnowPath << endl
               << "ffmpegPath=" << defaultFfmpegPath << endl
               << "fileBitrate=" << defaultFileBitrate << endl
               << "fileAudioDelay=" << defaultFileAudioDelay << endl
               << "visualizerMode=" << defaultVisualizerMode << endl
               << "desktopFramerate=" << defaultDesktopFramerate << endl
               << "desktopBitrate=" << defaultDesktopBitrate << endl
               << "desktopAudioDelay=" << defaultDesktopAudioDelay << endl
               << "threadQueueSize=" << defaultThreadQueueSize << endl;
    configFile.close();
}

void ConfigData::SaveConfigurationToFile()
{
    ofstream configFile(configFilePath);
    configFile << "castnowPath=" << castnowPath << endl
               << "ffmpegPath=" << ffmpegPath << endl
               << "fileBitrate=" << fileBitrate << endl
               << "fileAudioDelay=" << fileAudioDelay << endl
               << "visualizerMode=" << visualizerMode << endl
               << "desktopFramerate=" << desktopFramerate << endl
               << "desktopBitrate=" << desktopBitrate << endl
               << "desktopAudioDelay=" << desktopAudioDelay << endl
               << "threadQueueSize=" << threadQueueSize << endl;
    configFile.close();
}

void ConfigData::ProcessConfigFile()
{
    bool ConfigExists = CheckConfigFile();

    if(ConfigExists) ReadConfigFile();
    else CreateDefaultConfigFile();
}
