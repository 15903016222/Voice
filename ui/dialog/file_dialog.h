#ifndef __FILE_DIALOG_H__
#define __FILE_DIALOG_H__

#include <QDialog>
#include <QFileInfoList>
#include <QModelIndexList>
#include "base_dialog.h"

namespace Ui {
class FileDialog;
}

class QListWidgetItem;
class QStandardItemModel;


class FileDialog : public BaseDialog
{
    Q_OBJECT

public:
    struct S_FileDialogParameters {
        QString title;
        QString filePath;
        QStringList nameFilters;
        QString okButtonText;
        QString cancelButtonText;
    };

    explicit FileDialog(const S_FileDialogParameters &dialogParameters, QWidget *parent = 0);
    ~FileDialog();

    QString get_selected_file_name();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_cancelPushButton_clicked();
    void on_okPushButton_clicked();
    void do_fileListWidget_currentItenChanged(QListWidgetItem *current,QListWidgetItem *previous);

private:
    Ui::FileDialog *ui;
    QString        m_selectedFile;
    QFileInfoList  m_fileInfoList;

    void init_file_list(const QString &filePath, const QStringList &nameFilters);
};

#endif // __FILE_DIALOG_H__
