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
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime::currentTime());

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));

//    timer->start(1000);

}

void TimeSetDialog::on_dateEdit_dateChanged(QDate date)
{
    date = ui->dateEdit->date();
}

void TimeSetDialog::on_timeEdit_timeChanged(QTime time)
{
    time = ui->timeEdit->time();
}

void TimeSetDialog::on_pushButton_ok_clicked()
{
    ui->dateEdit->setReadOnly(true);
    ui->timeEdit->setReadOnly(true);
  //  close();

}

void TimeSetDialog::timeOutSlot()
{
    QDate date = ui->dateEdit->date();
    QTime time = ui->timeEdit->time();
    QTime time1(23, 59, 59);

    if(time == time1)
    {
     date = date.addDays(1);
    }
    time = time.addSecs(1);
    ui->dateEdit->setDate(date);
    ui->timeEdit->setTime(time);

}
