#include "mainwindow.h"
#include "formatselectionwindow.h"
#include "ui_mainwindow.h"
#include "outputwindow.h"
#include "youtubedl.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>


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
    if (!YoutubeDL::isValidUrl(this->ui->videoUrlEdit->text())) {
        QMessageBox::information(this, tr("Wrong URL"), tr("Please specify a valid URL"), QMessageBox::Ok);
        return;
    }

    int index = this->ui->modeComboBox->currentIndex();
    switch(index) {
    case 0: // Fetch url
        this->actionRetrieveUrl();
        break;
    case 1: // Download
        actionDownload();
        break;
    case 2: // Format download
        YoutubeDL ytdl;
        this->setCursor(Qt::WaitCursor);
        ytdl.fetchAvailableFormats(ui->videoUrlEdit->text());
        FormatSelectionWindow *formatWindow = new FormatSelectionWindow();
        formatWindow->setYoutubeDl(ytdl);
        formatWindow->setInputUrl(ui->videoUrlEdit->text());
        this->setCursor(Qt::ArrowCursor);
        break;
    }
}

void MainWindow::actionRetrieveUrl()
{
    this->setCursor(Qt::WaitCursor);
    YoutubeDL ytdl;
    QString output = ytdl.getUrl(this->ui->videoUrlEdit->text());
    OutputWindow *outputWindow = new OutputWindow();
    outputWindow->setText(output);
    outputWindow->show();
    this->setCursor(Qt::ArrowCursor);
}

void MainWindow::actionDownload()
{
    QString saveDirectory = QFileDialog::getExistingDirectory();
    if (!saveDirectory.isEmpty()) {
        OutputWindow *outputWindow = new OutputWindow();
        outputWindow->show();
        YoutubeDL ytdl;

        /*Ignores warings
            * good for systems without ffmpeg/avconv - otherwise download will stop
            * also good for playlist downloads with forbidden addresses
            as it will continue to download the rest of the playlist without stopping*/
        ytdl.addArguments("-i");

        if (ui->checkBoxAudioOnly->isChecked()) {
            ytdl.setFormat("bestaudio");
        }

        if (ui->checkBoxSubtitles->isChecked()) {
            ytdl.addArguments("--all-subs");
        }

        outputWindow->setYtdl(ytdl.getYtdl());
        outputWindow->connect(ytdl.getYtdl(), SIGNAL(readyRead()), outputWindow, SLOT(readyRead()));
        outputWindow->connect(ytdl.getYtdl(), SIGNAL(finished(int, QProcess::ExitStatus)), outputWindow, SLOT(downloadFinished(int, QProcess::ExitStatus)));
        ytdl.startDownload(this->ui->videoUrlEdit->text(), saveDirectory);
    }
}
