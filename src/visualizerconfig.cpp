#include "visualizerconfig.h"

using namespace std;

string fe_gain = "'1.4884e8 * f*f*f / (f*f + 424.36) / (f*f + 1.4884e8) / sqrt(f*f + 25122.25)'";
string fe_scale = "linlin";
string fe_wfunc = "tukey";
string fe_zero_phase = "on";
string fe_fft2 = "on";

string showcqt_fps = "60";
string showcqt_size = "1280x360";
string showcqt_count = "1";
string showcqt_csp = "bt470bg";
string showcqt_bar_g = "2";
string showcqt_sono_g = "4";
string showcqt_bar_v = "9";
string showcqt_sono_v = "17";
string showcqt_sono_h = "0";
string showcqt_bar_t = "0.5";
string showcqt_axis_h = "0";
string showcqt_tc = "0.33";
string showcqt_tlength = "'st(0,0.17); 384*tc / (384 / ld(0) + tc*f /(1-ld(0))) + 384*tc / (tc*f / ld(0) + 384 /(1-ld(0)))'";

string video_format = "yuv420p";

string VisualizerConfig::MusicVisualizer()
{
    stringstream ss;
    ss << " -filter_complex"
       << " \"firequalizer=gain=" << fe_gain
       << ":scale=" << fe_scale
       << ":wfunc=" << fe_wfunc
       << ":zero_phase=" << fe_zero_phase
       << ":fft2=" << fe_fft2
       << ",showcqt=fps=" << showcqt_fps
       << ":size=" << showcqt_size
       << ":count=" << showcqt_count
       << ":csp=" << showcqt_csp
       << ":bar_g=" << showcqt_bar_g
       << ":sono_g=" << showcqt_sono_g
       << ":bar_v=" << showcqt_bar_v
       << ":sono_v=" << showcqt_sono_v
       << ":sono_h=" << showcqt_sono_h
       << ":bar_t=" << showcqt_bar_t
       << ":axis_h=" << showcqt_axis_h
       << ":tc=" << showcqt_tc
       << ":tlength=" << showcqt_tlength
       << ",format=" << video_format
       << ",split [v0],vflip [v1]; [v0][v1] vstack [vis]\""
       << " -map [vis] -map 0:a"
       << " -preset superfast -tune animation"
       << " -c:v h264 -c:a copy";

    return ss.str();
}
