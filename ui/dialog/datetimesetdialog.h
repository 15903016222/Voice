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

    void retranslate_dialog_ui();
    void set_dialog_title(QMap<QString, QString> &map);
    void set_time_value(QString &string);
    void set_date_value(QString &string);
    void set_datetime_string(QString &str);

    QString get_date();
    QString get_time();

private:
    Ui::DateTimeSetDialog *ui;

    QMap<QString, QString> m_titleMap;

    QString m_strDate;
    QString m_strTime;
    QString m_strPre;

    QList<int> get_value_list(QString &text, QString &str);

private slots:
    void on_buttonBox_accepted();
    void check_date_valid(int number);
    void set_prefix(int value);

};

#endif // DATETIMESETDIALOG_H
