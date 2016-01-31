#include "mediaformat.h"

MediaFormat::MediaFormat()
{

}

QString MediaFormat::getFormatId() const
{
    return formatId;
}

void MediaFormat::setFormatId(const QString &value)
{
    formatId = value;
}

QString MediaFormat::getExtension() const
{
    return extension;
}

void MediaFormat::setExtension(const QString &value)
{
    extension = value;
}

QString MediaFormat::getResolution() const
{
    return resolution;
}

void MediaFormat::setResolution(const QString &value)
{
    resolution = value;
}

QString MediaFormat::getQuality() const
{
    return quality;
}

void MediaFormat::setQuality(const QString &value)
{
    quality = value;
}

QString MediaFormat::getNote() const
{
    return note;
}

void MediaFormat::setNote(const QString &value)
{
    note = value;
}

QString MediaFormat::getFormat() const
{
    return format;
}

void MediaFormat::setFormat(const QString &value)
{
    format = value;
}
