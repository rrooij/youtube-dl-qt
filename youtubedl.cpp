#include "youtubedl.h"

#include <QApplication>
#include <QRegExp>
#include <QRegExpValidator>
#include <QString>
#include <QStringList>
#include <QProcess>

YoutubeDL::YoutubeDL()
{
    #ifdef Q_OS_WIN
    this->program = QApplication::applicationDirPath() + "/youtube-dl.exe";
    #else
    this->program = "youtube-dl"; // assuming it is in PATH on other platforms
    #endif
    QObject *parent = QApplication::instance();
    this->ytdl = new QProcess(parent);
    this->ytdl->setProcessChannelMode(QProcess::MergedChannels);
}

QString YoutubeDL::getUrl(QString url)
{
    this->arguments << "-g" << url;
    this->ytdl->start(this->program, this->arguments);
    this->ytdl->waitForFinished();
    QString output(this->ytdl->readAllStandardOutput());
    return output;
}

bool YoutubeDL::isValidUrl(QString url)
{
    QRegExp urlRegex("^(http|https)://[a-z0-9]+([-.]{1}[a-z0-9]+)*.[a-z]{2,5}(([0-9]{1,5})?/?.*)$");
    QRegExpValidator validator(urlRegex);
    int index = 0;

    if(validator.validate(url, index) == QValidator::Acceptable) {
        return true;
    }
    return false;
}

void YoutubeDL::setFormat(QString format)
{
    this->arguments << "-f" << format;
}

void YoutubeDL::startDownload(QString url, QString workingDirectory)
{
    this->arguments << url;
    this->ytdl->setWorkingDirectory(workingDirectory);
    this->ytdl->start(this->program, this->arguments);
}

QProcess* YoutubeDL::getYtdl()
{
    return this->ytdl;
}
