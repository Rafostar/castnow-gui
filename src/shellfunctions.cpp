#include "shellfunctions.h"
#include <QFileDialog>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

FILE* shellProcess;

char ffmpegQuit[] = {'q'};

void ShellFunctions::CreateProcessPipe(const char* systemCommand)
{
    shellProcess = popen(systemCommand, "w");
}

void ShellFunctions::SendKeyToProcessPipe(char sendKey[])
{
    fwrite(sendKey, sizeof(char), sizeof(*sendKey), shellProcess);
    fflush(shellProcess);
}

void ShellFunctions::StopProcessPipe()
{
    SendKeyToProcessPipe(ffmpegQuit);
    if(shellProcess)
    pclose(shellProcess); // returns 0 (ffmpeg exited sucessfuly)
}

void ShellFunctions::FileStreamingVAAPI(string filePath)
{
    int startDelay = 0; // until "play from specified time" function is implemented

    stringstream ss;
    ss << "'" << confData->ffmpegPath
       << "' -hide_banner -ss " << startDelay
       << " -i '"<< filePath << "'"
       << " -itsoffset " << confData->fileAudioDelay
       << " -i '"<< filePath << "'"
       << " -map 0:v -map 1:a"
       << " -vaapi_device '/dev/dri/renderD128' -vf 'format=nv12,hwupload' -c:v h264_vaapi -level:v 4.1 -b:v " << confData->fileBitrate
       << "M -c:a copy -f matroska - | '" << confData->castnowPath << "' - " << confData->castnowLogCommand;

    string tmp = ss.str();
    //cout << "Running: " << tmp << endl; // for debug
    const char* castFile = tmp.c_str();

    CreateProcessPipe(castFile);
}

void ShellFunctions::LinkStreaming(string link)
{
    //Need to add to youtube-dl option force H264 here!!!

    stringstream ss;
    ss << "youtube-dl '" << link << "' -o - | '" << confData->castnowPath << "' - " << confData->castnowLogCommand;

    string tmp = ss.str();
    //cout << "Running: " << tmp << endl; // for debug
    const char* castLink = tmp.c_str();

    CreateProcessPipe(castLink);
}

void ShellFunctions::CaptureDeviceStreaming()
{
    stringstream ss;
    ss << "'" << confData->ffmpegPath
       << "' -hide_banner -f v4l2"
       << " -framerate 30"
       << " -video_size 640x480"
       << " -i /dev/video0"
       << " -pix_fmt yuv420p"
       << " -preset superfast"
       << " -c:v h264 -level:v 4.1"
       << " -f matroska - | '" << confData->castnowPath << "' - " << confData->castnowLogCommand;

    string tmp = ss.str();
    //cout << "Running: " << tmp << endl; // for debug
    const char* castLink = tmp.c_str();

    CreateProcessPipe(castLink);
}

void ShellFunctions::DesktopStreamingVAAPI()
{
    double startDelay = 5;
    double totalDelay = startDelay + confData->desktopAudioDelay;

    stringstream ss;
    ss << "'" << confData->ffmpegPath
       << "' -hide_banner"
       << " -video_size " << confData->desktopWidth << "x" << confData->desktopHeight
       << " -framerate " << confData->desktopFramerate
       << " -f x11grab"
       << " -thread_queue_size " << confData->threadQueueSize
       << " -i :0.0"
       << " -ss " << startDelay
       << " -f alsa"
       << " -thread_queue_size " << confData->threadQueueSize
       << " -ac 2 -itsoffset " << totalDelay
       << " -i default -vaapi_device '/dev/dri/renderD128' -vf 'format=nv12,hwupload' -c:v h264_vaapi -level:v 4.1 -b:v " << confData->desktopBitrate
       << "M -c:a flac -f matroska - | '" << confData->castnowPath << "' - " << confData->castnowLogCommand;

    string tmp = ss.str();
    //cout << "Running: " << tmp << endl; // for debug
    const char* castDesktop = tmp.c_str();

    CreateProcessPipe(castDesktop);
}

void ShellFunctions::AudioCDStreaming()
{
    int driveSpeed = 8;

    stringstream ss;
    ss << "'" << confData->ffmpegPath
       << "' -hide_banner"
       << " -f libcdio"
       << " -speed " << driveSpeed
       << " -i /dev/sr0";

    if(confData->visualizerMode == 2)
    {
        //CHECK COVER FUNCTION (INSTEAD OF BELOW LINE)
        ss << " -f wav - | '" << confData->castnowPath << "' - " << confData->castnowLogCommand;
    }
    else if(confData->visualizerMode == 1)
    {
        ss << visCfg->MusicVisualizer()
           << " -f matroska - | '" << confData->castnowPath << "' - " << confData->castnowLogCommand;
    }
    else
    {
        ss << " -f wav - | '" << confData->castnowPath << "' - " << confData->castnowLogCommand;
    }

    string tmp = ss.str();
    //cout << "Running: " << tmp << endl; // for debug
    const char* castCD = tmp.c_str();

    CreateProcessPipe(castCD);
}
