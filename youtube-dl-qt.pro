#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T16:49:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = /usr/bin
desktop.path = /usr/share/applications
desktop.files += tools/youtube-dl-qt.desktop
icon.path = /usr/share/icons/hicolor/scalable/apps
icon.files += tools/youtube-dl-qt-icon.svg
ICON = youtube-dl-qt.svg
TARGET = youtube-dl-qt
TEMPLATE = app

INSTALLS += target desktop icon


SOURCES += main.cpp\
        mainwindow.cpp \
    youtubedl.cpp \
    outputwindow.cpp \
    mediaformat.cpp \
    formatselectionwindow.cpp

HEADERS  += mainwindow.h \
    youtubedl.h \
    outputwindow.h \
    mediaformat.h \
    formatselectionwindow.h

FORMS    += mainwindow.ui \
    outputwindow.ui \
    formatselectionwindow.ui
