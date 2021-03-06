#include "outputwindow.h"
#include "ui_outputwindow.h"

#include <QDialog>
#include <QMessageBox>
#include <QProcess>

OutputWindow::OutputWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

OutputWindow::~OutputWindow()
{
    delete ui;
}

void OutputWindow::setText(QString text)
{
    this->ui->outputTextArea->document()->setPlainText(text);
}

void OutputWindow::setYtdl(QProcess *ytdl)
{
    this->ytdl = ytdl;
}


void OutputWindow::readyRead()
{
    this->ui->outputTextArea->document()->setPlainText(this->ytdl->readAll());
}

void OutputWindow::downloadFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::NormalExit) {
        QMessageBox::information(this, "Download succesful", "Download completed succesfully", QMessageBox::Ok);
        this->close();
    }
}
