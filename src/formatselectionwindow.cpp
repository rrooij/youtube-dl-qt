#include "formatselectionwindow.h"
#include "ui_formatselectionwindow.h"
#include "outputwindow.h"
#include "youtubedl.h"

#include <QAbstractItemView>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QVector>

FormatSelectionWindow::FormatSelectionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormatSelectionWindow)
{
    ui->setupUi(this);
    // Disable editing
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
        return;
    }
    ui->tableWidget->setRowCount(formats.length());
    for(int i = 0; i < formats.length(); ++i) {
        MediaFormat format = formats[i];
        QVector<QTableWidgetItem*> widgetItems;
        widgetItems.append(new QTableWidgetItem(format.getFormatId()));
        widgetItems.append(new QTableWidgetItem(format.getExtension()));
        widgetItems.append(new QTableWidgetItem(format.getFormat()));
        widgetItems.append(new QTableWidgetItem(format.getResolution()));
        widgetItems.append(new QTableWidgetItem(format.getAcodec()));
        widgetItems.append(new QTableWidgetItem(format.getVcodec()));

        for (int j = 0; j < widgetItems.length(); ++j) {
            ui->tableWidget->setItem(i, j, widgetItems[j]);
        }
    }
    show();
}

void FormatSelectionWindow::on_pushButton_clicked()
{
    QString saveDirectory = QFileDialog::getExistingDirectory();
    if (!saveDirectory.isEmpty()) {
        OutputWindow *outputWindow = new OutputWindow();
        outputWindow->show();
        int currentRow = ui->tableWidget->currentRow();
        QString format = ui->tableWidget->item(currentRow, 0)->text();
        youtubeDl = YoutubeDL();
        youtubeDl.setFormat(format);
        outputWindow->setYtdl(youtubeDl.getYtdl());
        outputWindow->connect(youtubeDl.getYtdl(), SIGNAL(readyRead()), outputWindow, SLOT(readyRead()));
        outputWindow->connect(ytdl.getYtdl(), SIGNAL(finished(int, QProcess::ExitStatus)), outputWindow, SLOT(finished(int, QProcess::ExitStatus)));
        youtubeDl.startDownload(inputUrl, saveDirectory);
        this->close();
    }

}

void FormatSelectionWindow::setInputUrl(const QString &value)
{
    inputUrl = value;
}
