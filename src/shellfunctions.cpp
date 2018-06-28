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


void shellfunctions::DesktopStreamingVAAPI(int videoX, int videoY, int fr, double audioDelay, double bitrate)
{
    double startDelay = 5;
    double totalDelay = startDelay + audioDelay;

    stringstream ss;
    ss << "ffmpeg -ss " << startDelay << " -video_size " << videoX << "x" << videoY << " -framerate " << fr << " -f x11grab -thread_queue_size 16 -i :0.0 -ss " << totalDelay << " -f alsa -thread_queue_size 16 -ac 2 -i default -vaapi_device /dev/dri/renderD128 -vf 'format=nv12,hwupload' -c:v h264_vaapi -b:v " << bitrate << "M -level:v 4.1 -c:a mp3 -f matroska - | castnow --quiet -";
    string tmp = ss.str();
    const char* CastDesktop = tmp.c_str();
    system(CastDesktop);
}
