# castnow-gui WIP
[![HitCount](http://hits.dwyl.io/Rafostar/castnow-gui.svg)](https://github.com/Rafostar/castnow-gui)
[![Donate](https://img.shields.io/badge/Donate-PayPal-blue.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=TFVDFD88KQ322)

castnow-gui - Qt interface for command-line chromecast player

## This project evolved into Gnome Shell Extension called [Cast to TV](https://github.com/Rafostar/gnome-shell-extension-cast-to-tv). All development has shifted to the new project.
## THIS IS AN UNFINISHED PROJECT!

### Requirements
Here is a list of required programs that castnow-gui depends on:
* [castnow](https://github.com/xat/castnow)
* [ffmpeg](https://ffmpeg.org)
* [youtube-dl](https://github.com/rg3/youtube-dl)

Please make sure you have all of the above installed before running castnow-gui.

Some of them might be available from your linux distro repos.
Try installing them with your package manager or follow the links for more info.
Currently **VAAPI encoding _is required_.** Make sure you have it installed.
More info and how to install VAAPI [here](https://wiki.archlinux.org/index.php/Hardware_video_acceleration).
Also desktop streaming probably does not work under **wayland** (I haven't tested it).

### Desktop streaming noise fix
Currently **default audio recording device** is used when streaming desktop.
If you are using **laptop** with build-in mic then usually default recording device is **microphone**.
If it is then you might hear **_amplified buzzing_** from your mic in your TV (better reduce TV volume to minimum before trying).

To fix this change default input device in your system configuration (using utility like **PulseAudio Volume Control**).

### Build from source
`qmake-qt5 castnow-gui.pro`

`make`

`sudo make install`

After that you can launch this program simply by running `castnow-gui` in terminal.

### To do:
- [X] Play file from specified path
- [X] Open file using file browser
- [X] Open network link
- [ ] Play files within folder function
- [ ] Play video+audio from youtube link
- [ ] Play audio only from youtube link
- [X] Convert video using ffmpeg on the fly
- [ ] Support for external subtitles
- [ ] Burn build-in subtitles (with fonts) to video
- [X] Play audio with music visualizer
- [X] VAAPI encoding for low cpu usage
- [ ] Start playing video from last point
- [ ] Stream video from selected time/chapter
- [X] Desktop streaming
- [X] Device video streaming (webcam, av-recorder etc.)

## Donation
If you like my work please support it by buying me a cup of coffee :grin:

[![PayPal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=TFVDFD88KQ322)
