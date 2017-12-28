#include "report_preview_dialog.h"
#include "ui_report_preview_dialog.h"
#include <ui/dialog/dpl_message_box.h>
#include <QFile>
#include <QDebug>
#include <QtWebKit/qwebview.h>
#include <QKeyEvent>

ReportPreviewDialog::ReportPreviewDialog(const QString &previewFilePath, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportPreviewDialog),
    m_webview(new QWebView(this))
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    m_file.setFileName(previewFilePath);
    ui->savePushButton->setFocus();
    ui->verticalLayout_2->insertWidget(0, m_webview);
}

ReportPreviewDialog::~ReportPreviewDialog()
{
    delete ui;
}

bool ReportPreviewDialog::preview()
{
    if((!m_file.exists()) || (!m_file.open(QIODevice::ReadOnly))) {
        return false;
    }

    m_webview->setHtml(QString::fromUtf8(m_file.readAll().constData()),QUrl("www.cndoppler.cn"));
    m_file.close();

    return true;
}

void ReportPreviewDialog::on_savePushButton_clicked()
{
    accept();
}

void ReportPreviewDialog::on_cancelPushButton_clicked()
{
    reject();
}

bool ReportPreviewDialog::event(QEvent *event)
{
    if(event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if(keyEvent->key() == Qt::Key_Return) {
            on_savePushButton_clicked();
            return true;
        }
    }

    return QDialog::event(event);
}
