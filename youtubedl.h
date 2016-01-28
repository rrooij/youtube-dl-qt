#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include <QProcess>

class YoutubeDL
{
public:
    YoutubeDL();
    ~YoutubeDL();
    QString getUrl(QString url);
private:
    QStringList arguments;
    QString program;
    QProcess *ytdl;
};

#endif // YOUTUBEDL_H
