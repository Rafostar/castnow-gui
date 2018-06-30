#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QDesktopWidget>
#include <string>

class ConfigData
{
public:
    static std::string castnowPath, ffmpegPath;

    static int desktopWidth, desktopHeight, desktopFramerate, threadQueueSize;

    static double desktopAudioDelay, desktopBitrate;
};

#endif // CONFIGDATA_H
