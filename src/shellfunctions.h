#ifndef SHELLFUNCTIONS_H
#define SHELLFUNCTIONS_H
#include <string>

using namespace std;

class ShellFunctions
{
public:
    //---Commands---//
    //std::string basicCommand = "screen -d -m -S cast_session"; // force new castnow_session
    //std::string basicCommand = ""; // it would be better to create process from code instead of screen command
    //std::string extraCommands = "";
    //std::string ffmpegPath = "ffmpeg";
    //std::string castnowPath = "castnow";
    //const char* stopRunningScreen = "screen -S cast_session -X stuff ^C > /dev/null"; //prevent running castnow more than once

    void CreateProcessPipe(const char* systemCommand);

    void StopProcessPipe();

    void SendKeyToProcessPipe(char sendKey[]);

    void FileStreamingVAAPI(string filePath);

    void LinkStreaming(string link);

    void DesktopStreamingVAAPI();
};

#endif // SHELLFUNCTIONS_H
