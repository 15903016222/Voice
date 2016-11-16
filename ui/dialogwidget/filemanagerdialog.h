#ifndef FILEMANAGERDIALOG_H
#define FILEMANAGERDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QStandardItemModel>

namespace Ui {
class FileManagerDialog;
}

class FileManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileManagerDialog(QWidget *parent = 0);
    ~FileManagerDialog();

private:
    Ui::FileManagerDialog *ui;

    QStandardItemModel *modelType;
    QStandardItemModel *modelSourcePath;
    QStandardItemModel *modelTargetPath;

    void init_type();
    void init_path();
    void init_source_path_tableView();
    void init_target_path_tableView();
    void set_tableView_header_data(QStandardItemModel *model);

    QStringList fileTypeList;
    QStringList filePathList;


private slots:
//    void onHeaderClicked(int index);
    void on_pushButton_close_clicked();
//    void on_tableView_1_clicked(const QModelIndex &index);
    void on_listView_clicked(const QModelIndex &index);
//    void on_tableView_2_clicked(const QModelIndex &index);
};

#endif // FILEMANAGERDIALOG_H
