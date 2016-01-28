#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "outputwindow.h"
#include "youtubedl.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int index = this->ui->modeComboBox->currentIndex();
    switch(index) {
    case 0: // Fetch url
        this->actionRetrieveUrl();
        break;
    case 1: // Download
        actionDownload();
        break;
    }
}

void MainWindow::actionRetrieveUrl()
{
    this->setCursor(Qt::WaitCursor);
    YoutubeDL *ytdl = new YoutubeDL();
    QString output = ytdl->getUrl(this->ui->videoUrlEdit->text());
    OutputWindow *outputWindow = new OutputWindow();
    outputWindow->setText(output);
    outputWindow->show();
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::actionDownload()
{
    QString saveDirectory = QFileDialog::getExistingDirectory();
    OutputWindow *outputWindow = new OutputWindow();
    outputWindow->show();
    YoutubeDL *ytdl = new YoutubeDL();
    outputWindow->setYtdl(ytdl->getYtdl());
    outputWindow->connect(ytdl->getYtdl(), SIGNAL(readyRead()), outputWindow, SLOT(readyRead()));
    ytdl->startDownload(this->ui->videoUrlEdit->text(), saveDirectory);
}
