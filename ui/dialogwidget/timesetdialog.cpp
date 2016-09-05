#include "timesetdialog.h"
#include "ui_timesetdialog.h"

TimeSetDialog::TimeSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TimeSetDialog)
{
    ui->setupUi(this);

    initUI();
}

TimeSetDialog::~TimeSetDialog()
{
    delete ui;
}

void TimeSetDialog::initUI()
{
    pushButton_ok.append(ui->pushButton_ok);
    dateEdit.append(ui->dateEdit);
    timeEdit.append(ui->timeEdit);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());
}

void TimeSetDialog::on_dateEdit_dateChanged(QDate date)
{
    date = ui->dateEdit->date();
}

void TimeSetDialog::on_timeEdit_timeChanged(QTime time)
{
    time = ui->timeEdit->time();
}
