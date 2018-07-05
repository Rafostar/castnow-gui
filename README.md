# castnow-gui WIP
castnow-gui - Qt interface for command-line chromecast player

## THIS IS A VERY EARLY WIP PROJECT!

### Requirements
Here is a list of required programs that castnow-gui depends on:
* [castnow](https://github.com/xat/castnow)
* [ffmpeg](https://ffmpeg.org)
* [youtube-dl](https://github.com/rg3/youtube-dl)

Please make sure you have all of the above installed before running castnow-gui.

Some of them might be available from your linux distro repos.
Try installing them with your package manager or follow the links for more info.

**Currently VAAPI encoding is required.** Make sure you have it installed.
More info and how to install VAAPI [here](https://wiki.archlinux.org/index.php/Hardware_video_acceleration).

### Install or update
`wget -N -P ~/.local/bin/ https://github.com/Rafostar/castnow-gui/raw/master/castnow-gui`

`sudo chmod +x ~/.local/bin/castnow-gui`

Or manually download castnow-gui file from root of this repo and set it as executable.

### To do:
- [X] Play file from specified path
- [X] Open file using file browser
- [ ] Open network link
- [ ] Play files within folder function
- [ ] Play video+audio from youtube link
- [ ] Play audio only from youtube link
- [X] Convert video using ffmpeg on the fly
- [ ] Support for external subtitles
- [ ] Burn build-in subtitles (with fonts) to video
- [ ] Play audio with cd art or visualizer
- [X] VAAPI encoding for low cpu usage
- [ ] Start playing video from last point
- [ ] Stream video from selected time/chapter
- [X] Desktop streaming
- [ ] Camera video streaming
