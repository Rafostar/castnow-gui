#ifndef SHELLFUNCTIONS_H
#define SHELLFUNCTIONS_H

#include "configdata.h"
#include "visualizerconfig.h"
#include <string>

using namespace std;

class ShellFunctions
{
public:
    void CreateProcessPipe(const char* systemCommand);

    void StopProcessPipe();

    void SendKeyToProcessPipe(char sendKey[]);

    void FileStreamingVAAPI(string filePath);

    void LinkStreaming(string link);

    void DesktopStreamingVAAPI();

    void CaptureDeviceStreaming();

    void MusicVisualizerStreaming(string filePath);

private:
    ConfigData *confData = new ConfigData;

    VisualizerConfig *visCfg = new VisualizerConfig;
};

#endif // SHELLFUNCTIONS_H
