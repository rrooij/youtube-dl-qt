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


SOURCES +=\
    src/formatselectionwindow.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mediaformat.cpp \
    src/outputwindow.cpp \
    src/youtubedl.cpp

HEADERS  += \
    src/formatselectionwindow.h \
    src/mainwindow.h \
    src/mediaformat.h \
    src/outputwindow.h \
    src/youtubedl.h

FORMS    += \
    src/formatselectionwindow.ui \
    src/mainwindow.ui \
    src/outputwindow.ui
