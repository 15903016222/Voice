#ifndef TIMESETDIALOG_H
#define TIMESETDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QDate>
#include <QTime>
#include <QPushButton>
#include <QDateEdit>
#include <QTimeEdit>

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
    QList<QPushButton*> pushButton_ok;
    QList<QDateEdit*> dateEdit;
    QList<QTimeEdit*> timeEdit;

private:
    void initUI();

signals:

public slots:

};

#endif // TIMESETDIALOG_H
