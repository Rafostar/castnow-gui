#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QDesktopWidget>
#include <QFile>
#include <string>
#include <sstream>

using namespace std;

class ConfigData
{
public:
    static string castnowPath, ffmpegPath;

    static string defaultCastnowPath, defaultFfmpegPath;

    static int desktopWidth, desktopHeight, desktopFramerate, threadQueueSize, visualizerMode;

    static int defaultDesktopFramerate, defaultThreadQueueSize, defaultVisualizerMode;

    static double fileBitrate, fileAudioDelay, desktopBitrate, desktopAudioDelay;

    static double defaultFileAudioDelay, defaultFileBitrate, defaultDesktopAudioDelay, defaultDesktopBitrate;

    static QFile castnowLogFile;

    static string castnowLogCommand;

    bool CheckConfigFile();

    void CreateDefaultConfigFile();

    void ReadConfigFile();

    void ProcessConfigFile();

    void SaveConfigurationToFile();
};

#endif // CONFIGDATA_H
