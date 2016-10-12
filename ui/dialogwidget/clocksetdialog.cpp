#include "clocksetdialog.h"
#include "ui_clocksetdialog.h"

#include <QTime>
#include <QTimer>

ClockSetDialog::ClockSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClockSetDialog)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdateTime()));
    timer->start(0);
}

ClockSetDialog::~ClockSetDialog()
{
    delete ui;
}

void ClockSetDialog::slotUpdateTime()
{
    str_time = QTime::currentTime().toString("hh:mm:ss");
    ui->spinBox_1->setValue(str_time.left(2).toInt());
    ui->spinBox_2->setValue(str_time.mid(3, 2).toInt());
    ui->spinBox_3->setValue(str_time.right(2).toInt());
}

void ClockSetDialog::on_buttonBox_accepted()
{
    int hour = ui->spinBox_1->value();
    int minute = ui->spinBox_2->value();
    int sec = ui->spinBox_3->value();

    str_time.clear();
    str_time.append(QString::number((double)hour, 'f', 0));
    str_time.append(":");
    str_time.append(QString::number((double)minute, 'f', 0));
    str_time.append(":");
    str_time.append(QString::number((double)sec, 'f', 0));

    emit currentTimeChanged(str_time);
}
