#include "mainwindow.h"
#include "formatselectionwindow.h"
#include "ui_mainwindow.h"
#include "outputwindow.h"
#include "youtubedl.h"

#include <QFileDialog>
#include <QMessageBox>


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
        ytdl.fetchAvailableFormats(ui->videoUrlEdit->text());
        FormatSelectionWindow *formatWindow = new FormatSelectionWindow();
        formatWindow->setYoutubeDl(ytdl);
        formatWindow->setInputUrl(ui->videoUrlEdit->text());
        formatWindow->show();
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

        if (ui->checkBoxAudioOnly->isChecked()) {
            ytdl.setFormat("bestaudio");
        }

        outputWindow->setYtdl(ytdl.getYtdl());
        outputWindow->connect(ytdl.getYtdl(), SIGNAL(readyRead()), outputWindow, SLOT(readyRead()));
        ytdl.startDownload(this->ui->videoUrlEdit->text(), saveDirectory);
    }
}
