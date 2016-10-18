#ifndef DATETIMESETDIALOG_H
#define DATETIMESETDIALOG_H

#include <QDialog>
#include <QMap>
#include <QDate>
#include <QTime>

namespace Ui {
class DateTimeSetDialog;
}

class DateTimeSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DateTimeSetDialog(QWidget *parent = 0);
    ~DateTimeSetDialog();

private:
    Ui::DateTimeSetDialog *ui;

public:
    void retranslate_dialog_ui();

    QMap<QString, QString> titleMap;
    QString str_date;
    QString str_time;

private:
    void init_ui();

signals:
    void currentDateTimeChanged(QString string);

public slots:
    void on_buttonBox_accepted();
    void check_date_valid(int number);
    void set_dialog_title(QMap<QString, QString> map);
    void set_spinbox_value(QList<int> valueList);

};

#endif // DATETIMESETDIALOG_H
