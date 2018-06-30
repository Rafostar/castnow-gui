#include "shellfunctions.h"
#include <QFileDialog>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>

using namespace std;

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
    ss << ffmpegPath << " -ss " << startDelay << " -video_size " << videoX << "x" << videoY << " -framerate " << framerate
       << " -f x11grab -thread_queue_size " << threadQueueSize << " -i :0.0 -itsoffset " << totalDelay << " -f alsa -thread_queue_size " << threadQueueSize
       << " -ac 2 -i default -vaapi_device ''/dev/dri/renderD128'' -vf 'format=nv12,hwupload' -c:v h264_vaapi -b:v " << bitrate
       << "M -level:v 4.1 -c:a flac -f matroska - | castnow --quiet - &";

    string tmp = ss.str();
    const char* castDesktop = tmp.c_str();
    system(castDesktop);
}
