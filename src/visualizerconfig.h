#ifndef VISUALIZERCONFIG_H
#define VISUALIZERCONFIG_H

#include "configdata.h"

using namespace std;

class VisualizerConfig
{
public:
    string MusicVisualizer();

private:
    ConfigData *confData = new ConfigData;
};

#endif // VISUALIZERCONFIG_H
