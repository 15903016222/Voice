#include "timesetdialog.h"
#include "ui_timesetdialog.h"

TimeSetDialog::TimeSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeSetDialog)
{
    ui->setupUi(this);

    init_ui();
}

TimeSetDialog::~TimeSetDialog()
{
    delete ui;
}

void TimeSetDialog::init_ui()
{
    pushButton_ok.append(ui->pushButton_ok);
    dateEdit.append(ui->dateEdit);
    timeEdit.append(ui->timeEdit);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
    ui->dateEdit->setCalendarPopup(true);
}

void TimeSetDialog::set_date_and_time(QString string)
{
    QString dateString = string.left(string.indexOf(" "));
    QString timeString = string.right(string.length() - string.indexOf(" ") - 1);
    QDate date = QDate(dateString.left(4).toInt(), dateString.mid(5, 2).toInt(), dateString.right(2).toInt());
    QTime time = QTime(timeString.left(2).toInt(), timeString.mid(3, 2).toInt(), timeString.right(2).toInt());
    ui->dateEdit->setDate(date);
    ui->timeEdit->setTime(time);
}
