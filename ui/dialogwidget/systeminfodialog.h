#ifndef SYSTEMINFODIALOG_H
#define SYSTEMINFODIALOG_H

#include <QDialog>

namespace Ui {
class SystemInfoDialog;
}

class SystemInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SystemInfoDialog(QWidget *parent = 0);
    ~SystemInfoDialog();

private:
    Ui::SystemInfoDialog *ui;

public:
    void retranslate_dialog_ui();

private:
    void read_textFile();

private slots:
//    void on_pushButton_credits_clicked();

};

#endif // SYSTEMINFODIALOG_H
