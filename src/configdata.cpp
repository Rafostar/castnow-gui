#include "configdata.h"
#include <QDesktopWidget>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

string configFilePath;

// ### CURRENT VALUES ### //
string ConfigData::castnowPath = "castnow";
string ConfigData::ffmpegPath = "ffmpeg";
int ConfigData::desktopWidth;
int ConfigData::desktopHeight;
int ConfigData::desktopFramerate = 30;
double ConfigData::desktopBitrate = 4;
double ConfigData::desktopAudioDelay = 0;
int ConfigData::threadQueueSize = 128;

// ### STORE DEFAULT VALUES ### //
const string defaultCastnowPath = ConfigData::castnowPath;
const string defaultffmpegPath = ConfigData::ffmpegPath;
const int defaultDesktopFramerate = ConfigData::desktopFramerate;
const double defaultDesktopBitrate = ConfigData::desktopBitrate;
const double defaultDesktopAudioDelay = ConfigData::desktopAudioDelay;
const int defaultThreadQueueSize = ConfigData::threadQueueSize;

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
               << "ffmpegPath=" << defaultffmpegPath << endl
               << "desktopFramerate=" << defaultDesktopFramerate << endl
               << "desktopBitrate=" << defaultDesktopBitrate << endl
               << "desktopAudioDelay=" << defaultDesktopAudioDelay << endl
               << "threadQueueSize=" << defaultThreadQueueSize << endl;
    configFile.close();
}
