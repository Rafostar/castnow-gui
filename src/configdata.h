#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <QDesktopWidget>

class ConfigData
{
public:
    static int desktopWidth, desktopHeight, desktopFramerate, threadQueueSize;
    static double desktopAudioDelay, desktopBitrate;
};

#endif // CONFIGDATA_H
