#ifndef VISUALIZERCONFIG_H
#define VISUALIZERCONFIG_H

#include "configdata.h"
#include "shellfunctions.h"
#include <string>

using namespace std;

class VisualizerConfig
{
public:
    void MusicVisualizer(string filePath);

private:
    ConfigData *confData = new ConfigData;

    ShellFunctions *shellFcn = new ShellFunctions;
};

#endif // VISUALIZERCONFIG_H
