#include "configdata.h"
#include <QDesktopWidget>
#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

string ConfigData::castnowPath = "castnow";
string ConfigData::ffmpegPath = "ffmpeg";
int ConfigData::desktopWidth;
int ConfigData::desktopHeight;
int ConfigData::desktopFramerate = 30;
int ConfigData::threadQueueSize = 128;
double ConfigData::desktopAudioDelay = 0.1;
double ConfigData::desktopBitrate = 3;

bool ConfigData::ProcessConfigFile()
{
    string configFilePath = "/home/";
    configFilePath += getlogin();
    configFilePath += "/.config/castnow-gui/castnow-gui.cfg";

    ifstream configFile;
    string configLine;
    configFile.open(configFilePath);

    while(getline(configFile, configLine))
    {
        istringstream currentLine(configLine);
        string configParamName;

        if(getline(currentLine, configParamName, '='))
        {
            cout << "Parameter is:" << configParamName;
            string configParamValue;
            if(getline(currentLine, configParamValue))
            {
                cout << ", value is:" << configParamValue << endl;
            }
          //Need to store values here
        }
    }
    configFile.close();
}
