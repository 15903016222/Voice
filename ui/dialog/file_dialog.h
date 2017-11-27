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
    enum E_Operation {
        CertImport,
        Update
    };

    enum E_FileType {
        FPGA,
        System
    };

    struct S_FileDialogParameters {
        QString title;
        QString filePath;
        QStringList nameFilters;
        QString okButtonText;
        QString cancelButtonText;
        E_Operation operation;
    };

    explicit FileDialog(const S_FileDialogParameters &dialogParameters, QWidget *parent = 0);
    ~FileDialog();

    QString get_selected_file_name();
    inline E_FileType  get_file_type() { return m_fileType; }

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_cancelPushButton_clicked();
    void on_okPushButton_clicked();
    void do_fileListWidget_currentItenChanged(QListWidgetItem *current,QListWidgetItem *previous);
    void slot_currentIndexChanged(int index);

private:
    Ui::FileDialog *ui;
    QString        m_selectedFile;
    QFileInfoList  m_fileInfoList;
    E_FileType     m_fileType;

    void init_file_list(const QString &filePath, const QStringList &nameFilters);
};

#endif // __FILE_DIALOG_H__
