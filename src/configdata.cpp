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

// ### DEFAULT VALUES ### //
string ConfigData::defaultCastnowPath = "castnow";
string ConfigData::defaultFfmpegPath = "ffmpeg";
int ConfigData::defaultDesktopFramerate = 30;
double ConfigData::defaultDesktopBitrate = 4;
double ConfigData::defaultDesktopAudioDelay = 0;
int ConfigData::defaultThreadQueueSize = 128;

// ### CURRENT VALUES STORAGE ### //
int ConfigData::desktopWidth;
int ConfigData::desktopHeight;
string ConfigData::castnowPath = ConfigData::castnowPath;
string ConfigData::ffmpegPath = ConfigData::ffmpegPath;
int ConfigData::desktopFramerate = ConfigData::desktopFramerate;
double ConfigData::desktopBitrate = ConfigData::desktopBitrate;
double ConfigData::desktopAudioDelay = ConfigData::desktopAudioDelay;
int ConfigData::threadQueueSize = ConfigData::threadQueueSize;

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
               << "desktopFramerate=" << defaultDesktopFramerate << endl
               << "desktopBitrate=" << defaultDesktopBitrate << endl
               << "desktopAudioDelay=" << defaultDesktopAudioDelay << endl
               << "threadQueueSize=" << defaultThreadQueueSize << endl;
    configFile.close();
}

void ConfigData::ProcessConfigFile()
{
    bool ConfigExists = CheckConfigFile();

    if(ConfigExists) ReadConfigFile();
    else CreateDefaultConfigFile();
}
