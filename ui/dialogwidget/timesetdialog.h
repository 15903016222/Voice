#ifndef TIMESETDIALOG_H
#define TIMESETDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDate>
#include <QTime>

namespace Ui {
class TimeSetDialog;
}

class TimeSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeSetDialog(QWidget *parent = 0);
    ~TimeSetDialog();

private:
    Ui::TimeSetDialog *ui;

public:


private:
    void initUI();

signals:

private slots:
    void on_dateEdit_dateChanged(QDate date);
    void on_timeEdit_timeChanged(QTime time);
    void on_pushButton_ok_clicked();
    void timeOutSlot();

};

#endif // TIMESETDIALOG_H
