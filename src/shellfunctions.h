#ifndef SHELLFUNCTIONS_H
#define SHELLFUNCTIONS_H
#include <string>

class shellfunctions
{
public:
    int desktopWidth, desktopHeight;
    //---Commands---//
    std::string BasicCommand = "screen -d -m -S cast_session castnow"; // force new castnow_session
    std::string ExtraCommands = "";
    const char* StopRunningScreen = "screen -S cast_session -X stuff ^C > /dev/null"; //prevent running castnow more than once

    void ffmpegEncode();
    void DesktopStreamingVAAPI(int videoX, int videoY, int fr, double audioDelay, double bitrate);
};

#endif // SHELLFUNCTIONS_H
