/**
 * @file    report_preview_dialog.h
 * @brief   报表预览窗口，用于报表预览，保存报表。
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_PREVIEW_DIALOG_H__
#define __REPORT_PREVIEW_DIALOG_H__

#include <QDialog>
#include <QFile>

namespace Ui {
class ReportPreviewDialog;
}

class ReportPreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportPreviewDialog(const QString &previewFilePath, QWidget *parent = 0);
    ~ReportPreviewDialog();
    bool preview();

private slots:
    void on_savePushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::ReportPreviewDialog *ui;
    QFile   m_file;
};

#endif // __REPORT_PREVIEW_DIALOG_H__
