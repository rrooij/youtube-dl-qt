#include "outputwindow.h"
#include "ui_outputwindow.h"

#include <QDialog>
#include <QMessageBox>

OutputWindow::OutputWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWindow)
{
    ui->setupUi(this);
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
