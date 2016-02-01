#include "formatselectionwindow.h"
#include "ui_formatselectionwindow.h"
#include "outputwindow.h"
#include "youtubedl.h"

#include <QFileDialog>
#include <QTableWidgetItem>
#include <QMessageBox>

FormatSelectionWindow::FormatSelectionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormatSelectionWindow)
{
    ui->setupUi(this);
}

FormatSelectionWindow::~FormatSelectionWindow()
{
    delete ui;
}

void FormatSelectionWindow::setYoutubeDl(const YoutubeDL &value)
{
    youtubeDl = value;
    populateTable(youtubeDl.getFormats());
}

void FormatSelectionWindow::populateTable(QVector<MediaFormat> formats)
{
    if (formats.length() == 0) {
        QMessageBox::information(this, "No formats found", "No formats found. Note that playlists aren't supported yet", QMessageBox::Ok);
        this->close();
    }
    ui->tableWidget->setRowCount(formats.length());
    for(int i = 0; i < formats.length(); ++i) {
        MediaFormat format = formats[i];
        QTableWidgetItem* formatId = new QTableWidgetItem(format.getFormatId());
        QTableWidgetItem* extension = new QTableWidgetItem(format.getExtension());
        QTableWidgetItem* formatText = new QTableWidgetItem(format.getFormat());
        ui->tableWidget->setItem(i, 0, formatId);
        ui->tableWidget->setItem(i, 1, extension);
        ui->tableWidget->setItem(i, 2, formatText);
    }
}

void FormatSelectionWindow::on_pushButton_clicked()
{
    QString saveDirectory = QFileDialog::getExistingDirectory();
    if (!saveDirectory.isEmpty()) {
        OutputWindow *outputWindow = new OutputWindow();
        outputWindow->show();
        int currentRow = ui->tableWidget->currentRow();
        QString format = ui->tableWidget->itemAt(0, currentRow)->text();
        youtubeDl = YoutubeDL();
        youtubeDl.setFormat(format);
        outputWindow->setYtdl(youtubeDl.getYtdl());
        outputWindow->connect(youtubeDl.getYtdl(), SIGNAL(readyRead()), outputWindow, SLOT(readyRead()));
        youtubeDl.startDownload(inputUrl, saveDirectory);
        this->destroy(true, false);
    }

}

void FormatSelectionWindow::setInputUrl(const QString &value)
{
    inputUrl = value;
}
