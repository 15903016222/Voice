#ifndef FILEMANAGERDIALOG_H
#define FILEMANAGERDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QTableView>

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

    void init_path();
    void init_source_path_tableView();
    void init_target_path_tableView();
    void set_tableView_header_data(QFileSystemModel *model);
    void copy_file_to_path(QString fromDir, QString toDir);
    void do_file_filters(QTableView *view, QFileSystemModel *model, const QString &str);

    QStringList m_filePathList;
    QStringList m_listSetup;
    QStringList m_listData;
    QStringList m_listReport;
    QStringList m_listImage;
    QStringList m_listCAD;
    QStringList m_listAll;
    bool m_clickedTableView1;
    bool m_clickedTableView2;
    QModelIndex m_clickedIndex1;
    QModelIndex m_clickedIndex2;
    QFileSystemModel *m_modelSource;
    QFileSystemModel *m_modelTarget;

private slots:
    void on_pushButton_close_clicked();
    void on_listWidget_clicked(const QModelIndex &index);
    void do_header1_clicked(int index);
    void do_header2_clicked(int index);
    void on_tableView_1_pressed(const QModelIndex &index);
    void on_tableView_2_pressed(const QModelIndex &index);
    void on_pushButton_select_clicked();
    void on_pushButton_selectAll_clicked();
    void on_pushButton_rename_clicked();
    void on_comboBox_1_currentIndexChanged(const QString &arg1);
    void on_comboBox_2_currentIndexChanged(const QString &arg1);
    void on_pushButton_copy_clicked();
    void on_pushButton_move_clicked();
    void on_pushButton_delete_clicked();
};

#endif // FILEMANAGERDIALOG_H
