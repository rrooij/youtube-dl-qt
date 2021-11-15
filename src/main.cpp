#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Youtube Downloader");
    a.setApplicationVersion("0.6");
    MainWindow w;
    w.show();

    return a.exec();
}
