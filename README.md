#youtube-dl-qt

Simple QT-frontend for youtube-dl. It only supports retrieving a video URL for now.

It is assumed that youtube-dl is in PATH.

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
