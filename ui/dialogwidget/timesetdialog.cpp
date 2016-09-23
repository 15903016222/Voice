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
    ui->dateEdit->setCalendarPopup(true);
}
