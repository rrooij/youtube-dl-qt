#ifndef YOUTUBEDL_H
#define YOUTUBEDL_H

#include "mediaformat.h"

#include <QJsonObject>
#include <QProcess>
#include <QVector>

class YoutubeDL
{
public:
    YoutubeDL();
    QJsonObject createJsonObject(QString url);
    void fetchAvailableFormats(QString url);
    QString getUrl(QString url);
    QProcess *getYtdl();
    void resetArguments();
    static bool isValidUrl(QString url);
    void setFormat(QString format);
    void startDownload(QString url, QString workingDirectory);
    QVector<MediaFormat> getFormats() const;
    void setFormats(const QVector<MediaFormat> &value);
    void addArguments(QString arg);

private:
    QStringList arguments;
    QVector<MediaFormat> formats;
    QString program;
    QProcess *ytdl;
};

#endif // YOUTUBEDL_H
