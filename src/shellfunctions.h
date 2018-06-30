#ifndef SHELLFUNCTIONS_H
#define SHELLFUNCTIONS_H
#include <string>

class ShellFunctions
{
public:
    //---Commands---//
    std::string basicCommand = "screen -d -m -S cast_session"; // force new castnow_session
    //std::string basicCommand = ""; // it would be better to create process from code instead of screen command
    std::string extraCommands = "";
    //std::string ffmpegPath = "ffmpeg";
    //std::string castnowPath = "castnow";
    const char* stopRunningScreen = "screen -S cast_session -X stuff ^C > /dev/null"; //prevent running castnow more than once

    void ffmpegEncode();
    void DesktopStreamingVAAPI(int videoX, int videoY, int framerate, int threadQueueSize, double audioDelay, double bitrate);
};

#endif // SHELLFUNCTIONS_H
