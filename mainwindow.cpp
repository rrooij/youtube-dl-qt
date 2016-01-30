#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "outputwindow.h"
#include "youtubedl.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>


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
    if (!isValidUrl(this->ui->videoUrlEdit->text())) {
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

bool MainWindow::isValidUrl(QString url)
{
    QRegExp urlRegex("^(http|https)://[a-z0-9]+([-.]{1}[a-z0-9]+)*.[a-z]{2,5}(([0-9]{1,5})?/?.*)$");
    QRegExpValidator validator(urlRegex);
    int index = 0;

    if(validator.validate(url, index) == QValidator::Acceptable) {
        return true;
    }
    return false;
}

void MainWindow::actionDownload()
{
    QString saveDirectory = QFileDialog::getExistingDirectory();
    if (!saveDirectory.isEmpty()) {
        OutputWindow *outputWindow = new OutputWindow();
        outputWindow->show();
        YoutubeDL ytdl;

        if (ui->checkBoxAudioOnly->isChecked()) {
            ytdl.setFormat("bestaudio");
        }

        outputWindow->setYtdl(ytdl.getYtdl());
        outputWindow->connect(ytdl.getYtdl(), SIGNAL(readyRead()), outputWindow, SLOT(readyRead()));
        ytdl.startDownload(this->ui->videoUrlEdit->text(), saveDirectory);
    }
}
