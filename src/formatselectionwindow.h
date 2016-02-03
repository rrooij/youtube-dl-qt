#ifndef FORMATSELECTIONWINDOW_H
#define FORMATSELECTIONWINDOW_H

#include <QVector>
#include <QWidget>

#include "mediaformat.h"
#include "youtubedl.h"

namespace Ui {
class FormatSelectionWindow;
}

class FormatSelectionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FormatSelectionWindow(QWidget *parent = 0);
    ~FormatSelectionWindow();

    void setYoutubeDl(const YoutubeDL &value);

    void setFormats(const QVector<MediaFormat> &value);

    void setInputUrl(const QString &value);

private slots:
    void on_pushButton_clicked();

private:
    Ui::FormatSelectionWindow *ui;
    QString inputUrl;
    YoutubeDL youtubeDl;
    void populateTable(QVector<MediaFormat>);
};

#endif // FORMATSELECTIONWINDOW_H
