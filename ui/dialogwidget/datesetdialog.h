#ifndef DATESETDIALOG_H
#define DATESETDIALOG_H

#include <QDialog>

namespace Ui {
class DateSetDialog;
}

class DateSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateSetDialog(QWidget *parent = 0);
    ~DateSetDialog();

private:
    Ui::DateSetDialog *ui;

public:
    void retranslate_dialog_ui();
    QString str_date;

private:
    void init_ui();

signals:
    void currentDateChanged(QString date);

public slots:
    void on_buttonBox_accepted();
    void check_date_valid(int number);

};

#endif // DATESETDIALOG_H
