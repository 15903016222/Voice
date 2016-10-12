#ifndef CLOCKSETDIALOG_H
#define CLOCKSETDIALOG_H

#include <QDialog>

namespace Ui {
class ClockSetDialog;
}

class ClockSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClockSetDialog(QWidget *parent = 0);
    ~ClockSetDialog();

private:
    Ui::ClockSetDialog *ui;

public:
    void retranslate_dialog_ui();
    QString str_time;

private:

signals:
    void currentTimeChanged(QString time);

public slots:
    void slotUpdateTime();
    void on_buttonBox_accepted();

};

#endif // CLOCKSETDIALOG_H
