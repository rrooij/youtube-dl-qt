#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "youtubedl.h"
#include "outputwindow.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void actionRetrieveUrl();
    void actionDownload();
};

#endif // MAINWINDOW_H
