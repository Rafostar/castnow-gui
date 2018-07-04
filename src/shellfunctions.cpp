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
    pclose(shellProcess); // returns int 0 (ffmpeg exited sucessfuly)
}

void ShellFunctions::DesktopStreamingVAAPI()
{
    double startDelay = 5;
    double totalDelay = startDelay + confDataSF.desktopAudioDelay;

    //system("sudo killall ffmpeg"); // Temporary (and ugly) method to stop ffmpeg
    //system(stopRunningScreen);

    stringstream ss;
    ss << confDataSF.ffmpegPath << " -ss " << startDelay << " -video_size " << confDataSF.desktopWidth << "x" << confDataSF.desktopHeight << " -framerate " << confDataSF.desktopFramerate
       << " -f x11grab -thread_queue_size " << confDataSF.threadQueueSize << " -i :0.0 -f alsa -thread_queue_size " << confDataSF.threadQueueSize << " -ac 2 -itsoffset " << totalDelay
       << " -i default -vaapi_device '/dev/dri/renderD128' -vf 'format=nv12,hwupload' -c:v h264_vaapi -level:v 4.1 -b:v " << confDataSF.desktopBitrate
       << "M -c:a flac -f matroska - | " << confDataSF.castnowPath << " --quiet -";

    string tmp = ss.str();
    cout << "Running: " << tmp << endl; // for debug
    const char* castDesktop = tmp.c_str();

    CreateProcessPipe(castDesktop);
    //system(castDesktop);
}
