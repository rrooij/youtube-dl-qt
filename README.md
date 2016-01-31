#youtube-dl-qt

Simple QT-frontend for [youtube-dl](https://rg3.github.io/youtube-dl/).

It is assumed that youtube-dl is in PATH.

## Installing

### GNU/Linux
Check out the [requirements](#requirements). You can choose to compile the binary yourself or
use the binary I compiled (found in Releases). Be sure to give the binary execution rights.


### Windows
There is an executable installer for Windows found in the releases called `setup_windows.exe`.
A portable version can be found in the 7zip archive `youtube-dl-qt-windows`.

## Requirements

### GNU/Linux

* Qt5
* youtube-dl

Both are available in most repositories.

## Compiling

First, clone the git repository.

`clone git@github.com:rrooij/youtube-dl-qt.git`

Go into the directory:

`cd youtube-dl-qt`

Run:

```
make clean
qmake -config release
make
```

The executable should be named `youtube-dl-qt` and can be run by `./youtube-dl-qt`.


