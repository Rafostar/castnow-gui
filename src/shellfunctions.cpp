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

void ffmpegEncode()
{

}


void ShellFunctions::DesktopStreamingVAAPI(int videoX, int videoY, int framerate, int threadQueueSize, double audioDelay, double bitrate)
{
    double startDelay = 5;
    double totalDelay = startDelay + audioDelay;

    system("sudo killall ffmpeg"); // Temporary (and ugly) method to stop ffmpeg
    system(stopRunningScreen);

    stringstream ss;
    ss << confDataSF.ffmpegPath << " -ss " << startDelay << " -video_size " << videoX << "x" << videoY << " -framerate " << framerate
       << " -f x11grab -thread_queue_size " << threadQueueSize << " -i :0.0 -f alsa -thread_queue_size " << threadQueueSize << " -ac 2 -itsoffset " << totalDelay
       << " -i default -vaapi_device '/dev/dri/renderD128' -vf 'format=nv12,hwupload' -c:v h264_vaapi -level:v 4.1 -b:v " << bitrate
       << "M -c:a flac -f matroska - | " << confDataSF.castnowPath << " --quiet - &";

    string tmp = ss.str();
    cout << "Running: " << tmp;
    const char* castDesktop = tmp.c_str();
    //system(castDesktop);
}
