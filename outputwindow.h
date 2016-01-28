#ifndef OUTPUTWINDOW_H
#define OUTPUTWINDOW_H

#include <QProcess>
#include <QWidget>

namespace Ui {
class OutputWindow;
}

class OutputWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OutputWindow(QWidget *parent = 0);
    ~OutputWindow();
    void setText(QString text);
    void updateOutput(QProcess* process);

    void setYtdl(QProcess* ytdl);

public slots:
    void readyRead();

private:
    Ui::OutputWindow *ui;
    QProcess* ytdl;
};

#endif // OUTPUTWINDOW_H
