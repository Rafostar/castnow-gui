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

    static double desktopAudioDelay, desktopBitrate;

    static double defaultDesktopAudioDelay, defaultDesktopBitrate;

    bool CheckConfigFile();

    void CreateDefaultConfigFile();

    void ReadConfigFile();

    void ProcessConfigFile();
};

#endif // CONFIGDATA_H
