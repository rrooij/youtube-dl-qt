#include "youtubedl.h"

#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValueRef>
#include <QRegExp>
#include <QRegExpValidator>
#include <QString>
#include <QStringList>
#include <QProcess>
#include <QVariantList>

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

QJsonObject YoutubeDL::createJsonObject(QString url)
{
    arguments << "-j" << url;
    ytdl->setProcessChannelMode(QProcess::SeparateChannels);
    ytdl->start(this->program, this->arguments);
    ytdl->waitForFinished();
    QByteArray output(this->ytdl->readAllStandardOutput());
    QJsonDocument json = QJsonDocument::fromJson(output);
    return json.object();
}

void YoutubeDL::fetchAvailableFormats(QString url)
{
    QVector<MediaFormat> formats;
    QJsonObject jsonObject = createJsonObject(url);
    QJsonArray jsonFormats = jsonObject["formats"].toArray();
    QJsonArray::iterator i;

    for (i = jsonFormats.begin(); i != jsonFormats.end(); ++i) {
        QJsonValue value = *i;
        QJsonObject formatObject = value.toObject();
        MediaFormat format;
        format.setFormatId(formatObject["format_id"].toString());
        format.setFormat(formatObject["format"].toString());
        format.setExtension(formatObject["ext"].toString());
        format.setNote(formatObject["format_note"].toString());
        formats.append(format);
    }
    this->formats = formats;
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

QVector<MediaFormat> YoutubeDL::getFormats() const
{
    return formats;
}

void YoutubeDL::setFormats(const QVector<MediaFormat> &value)
{
    formats = value;
}

QProcess* YoutubeDL::getYtdl()
{
    return this->ytdl;
}

void YoutubeDL::resetArguments()
{
    this->arguments.clear();
}
