#include "clocksetdialog.h"
#include "ui_clocksetdialog.h"

#include <QTime>

ClockSetDialog::ClockSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClockSetDialog)
{
    ui->setupUi(this);

    init_ui();
}

ClockSetDialog::~ClockSetDialog()
{
    delete ui;
}

void ClockSetDialog::init_ui()
{
    QString str_time = QTime::currentTime().toString("hh:mm:ss");
    ui->spinBox_1->setValue(str_time.left(2).toInt());
    ui->spinBox_2->setValue(str_time.mid(3, 2).toInt());
    ui->spinBox_3->setValue(str_time.right(2).toInt());
}
