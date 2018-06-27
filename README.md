# castnow-gui WIP
castnow-gui - Qt interface for command-line chromecast player

## THIS IS A VERY EARLY WIP PROJECT - DON'T DOWNLOAD YET!

### Requirements
Here is a list of required programs that castnow-gui depends on:
* [castnow](https://github.com/xat/castnow)
* [screen](https://www.gnu.org/software/screen)
* [zenity](https://github.com/GNOME/zenity)
* [ffmpeg](https://github.com/FFmpeg/FFmpeg)
* [youtube-dl](https://github.com/rg3/youtube-dl)

Please make sure you have all of the above installed before running castnow-gui.

Most of them should be availible from your linux distro repos.
Try installing them with your package manager or follow the links for more info.

### Install or update
`wget -N -P ~/.local/bin/ https://github.com/Rafostar/castnow-gui/raw/master/castnow-gui`

`sudo chmod +x ~/.local/bin/castnow-gui`

Or manually download castnow-gui file from root of this repo and set it as executable.

### To do:
- [X] Play file from specified path
- [ ] Open file using file browser
- [ ] Open network link
- [ ] Play files within folder function
- [ ] Play video+audio from youtube link
- [ ] Play audio only from youtube link
- [ ] Convert video using ffmpeg on fly
- [ ] Support for external subtitles
- [ ] Burn build-in subtitles (with fonts) to video
- [ ] Play audio with cd art or visualizer
- [ ] VAAPI encoding for low cpu usage
- [ ] Start playing video from last point
- [ ] Stream video from selected time/chapter
