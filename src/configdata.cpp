#include "configdata.h"
#include <QDesktopWidget>

using namespace std;

string ConfigData::castnowPath = "castnow";
string ConfigData::ffmpegPath = "ffmpeg";
int ConfigData::desktopWidth;
int ConfigData::desktopHeight;
int ConfigData::desktopFramerate = 30;
int ConfigData::threadQueueSize = 128;
double ConfigData::desktopAudioDelay = 0.1;
double ConfigData::desktopBitrate = 3;
