#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QDesktopWidget>
#include <string>

class ConfigData
{
public:
    static std::string castnowPath, ffmpegPath;

    static std::string defaultCastnowPath, defaultFfmpegPath;

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
