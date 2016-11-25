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
    void set_dialog_title(QMap<QString, QString> map);
    void set_spinbox_value(QList<int> valueList);

    QString m_strDate;
    QString m_strTime;

private:
    Ui::DateTimeSetDialog *ui;

    QMap<QString, QString> titleMap;

signals:
    void currentDateTimeChanged(QString string);

public slots:
    void on_buttonBox_accepted();
    void check_date_valid(int number);

};

#endif // DATETIMESETDIALOG_H
