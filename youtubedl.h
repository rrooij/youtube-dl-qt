#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QProcess>

class YoutubeDL
{
public:
    YoutubeDL();
    QString getUrl(QString url);
    QProcess *getYtdl();
    void startDownload(QString url, QString workingDirectory);
private:
    QStringList arguments;
    QString program;
    QProcess *ytdl;
    void setFormat(QString format);
};

#endif // YOUTUBEDL_H
