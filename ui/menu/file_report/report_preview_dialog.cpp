#include "report_preview_dialog.h"
#include "ui_report_preview_dialog.h"
#include <ui/dialog/dpl_message_box.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>

ReportPreviewDialog::ReportPreviewDialog(const QString &previewFilePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportPreviewDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_file.setFileName(previewFilePath);
}

ReportPreviewDialog::~ReportPreviewDialog()
{
    delete ui;
}

bool ReportPreviewDialog::preview()
{
    if((!m_file.exists()) || (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))) {
        qDebug() << "[" << __FUNCTION__ << "]" << "false";
        return false;
    }

    QTextStream textStream(&m_file);
    ui->reportLabel->setText(QString::fromUtf8(textStream.readAll().toStdString().c_str()));
    m_file.close();
    return true;
}

void ReportPreviewDialog::on_savePushButton_clicked()
{
    DplMessageBox messageBox(QMessageBox::Information, tr("Info"), tr("Create Success!"));
    messageBox.exec();
    accept();
}

void ReportPreviewDialog::on_cancelPushButton_clicked()
{
    m_file.remove();
    reject();
}
