#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QDesktopWidget>
#include <string>

using namespace std;

class ConfigData
{
public:
    static string castnowPath, ffmpegPath;

    static string defaultCastnowPath, defaultFfmpegPath;

    static int desktopWidth, desktopHeight, desktopFramerate, threadQueueSize;

    static int defaultDesktopFramerate, defaultThreadQueueSize;

    static double fileBitrate, fileAudioDelay, desktopBitrate, desktopAudioDelay;

    static double defaultFileAudioDelay, defaultFileBitrate, defaultDesktopAudioDelay, defaultDesktopBitrate;

    bool CheckConfigFile();

    void CreateDefaultConfigFile();

    void ReadConfigFile();

    void ProcessConfigFile();

    void SaveConfigurationToFile();
};

#endif // CONFIGDATA_H
