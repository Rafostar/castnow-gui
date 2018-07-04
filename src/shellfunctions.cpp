#include "shellfunctions.h"
#include "configdata.h"
#include <QFileDialog>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

ConfigData confDataSF;

FILE* shellProcess;

char ffmpegQuit[] = {'q'};

void ShellFunctions::CreateProcessPipe(const char* systemCommand)
{
    shellProcess = popen(systemCommand, "w");
    cout << "Created new ffmpeg process" << endl;
}

void ShellFunctions::SendKeyToProcessPipe(char sendKey[])
{
    fwrite(sendKey, sizeof(char), sizeof(*sendKey), shellProcess);
    fflush(shellProcess);
}

void ShellFunctions::StopProcessPipe()
{
    SendKeyToProcessPipe(ffmpegQuit);
    pclose(shellProcess); // returns 0 (ffmpeg exited sucessfuly)
}

void ShellFunctions::FileStreamingVAAPI(string filePath)
{
    int startDelay = 0; // until "play from specified time" function is implemented

    stringstream ss;
    ss << confDataSF.ffmpegPath
       << " -hide_banner -ss " << startDelay
       << " -i '"<< filePath << "'"
       << " -itsoffset " << confDataSF.fileAudioDelay
       << " -i '"<< filePath << "'"
       << " -map 0:v -map 1:a"
       << " -vaapi_device '/dev/dri/renderD128' -vf 'format=nv12,hwupload' -c:v h264_vaapi -level:v 4.1 -b:v " << confDataSF.fileBitrate
       << "M -c:a copy -f matroska - | " << confDataSF.castnowPath << " --quiet -";

    string tmp = ss.str();
    cout << "Running: " << tmp << endl; // for debug
    const char* castFile = tmp.c_str();

    CreateProcessPipe(castFile);
}

void ShellFunctions::DesktopStreamingVAAPI()
{
    double startDelay = 5;
    double totalDelay = startDelay + confDataSF.desktopAudioDelay;

    stringstream ss;
    ss << confDataSF.ffmpegPath
       << " -hide_banner -ss " << startDelay
       << " -video_size " << confDataSF.desktopWidth << "x" << confDataSF.desktopHeight
       << " -framerate " << confDataSF.desktopFramerate
       << " -f x11grab -thread_queue_size " << confDataSF.threadQueueSize
       << " -i :0.0 -f alsa -thread_queue_size " << confDataSF.threadQueueSize
       << " -ac 2 -itsoffset " << totalDelay
       << " -i default -vaapi_device '/dev/dri/renderD128' -vf 'format=nv12,hwupload' -c:v h264_vaapi -level:v 4.1 -b:v " << confDataSF.desktopBitrate
       << "M -c:a flac -f matroska - | " << confDataSF.castnowPath << " --quiet -";

    string tmp = ss.str();
    cout << "Running: " << tmp << endl; // for debug
    const char* castDesktop = tmp.c_str();

    CreateProcessPipe(castDesktop);
}
