/**
 * @file base_open_file_dialog.h
 * @brief 打开配置、数据文件的对话窗口
 */

#ifndef __BASE_OPEN_FILE_DIALOG_H__
#define __BASE_OPEN_FILE_DIALOG_H__

#include <QDialog>
#include <QDir>
#include <QStandardItemModel>

namespace Ui {
class BaseOpenFileDialog;
}

class BaseOpenFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseOpenFileDialog(const QString &basePath, QWidget *parent = 0);
    ~BaseOpenFileDialog();

    /**
     * @brief get_selected_file 获取将要打开的文件路径
     * @return  将打开的文件路径
     */
    QString get_selected_file() const;


protected slots:

    void on_openBtn_clicked();
    void on_cancleBtn_clicked();
    void on_backBtn_clicked();
    void do_filesTasbleView_clicked(const QModelIndex &index);
    void do_filesTableView_current_row_changed(const QModelIndex &current, const QModelIndex &previous);


private:
    Ui::BaseOpenFileDialog *ui;
    QString                 m_basePath;
    QFileInfoList           m_currentFileList;
    QStandardItemModel      *m_standardItemModel;

    QFileInfoList get_file_list(const QString &path);
    void update_model();

    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);

};

#endif // __BASE_OPEN_FILE_DIALOG_H__
