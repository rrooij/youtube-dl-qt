#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QProcess>

class YoutubeDL
{
public:
    YoutubeDL();
    QString getUrl(QString url);
    QProcess *getYtdl();
    static bool isValidUrl(QString url);
    void setFormat(QString format);
    void startDownload(QString url, QString workingDirectory);
private:
    QStringList arguments;
    QString program;
    QProcess *ytdl;    
};

#endif // YOUTUBEDL_H
