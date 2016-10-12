#include "datesetdialog.h"
#include "ui_datesetdialog.h"

#include <QDate>

DateSetDialog::DateSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateSetDialog)
{
    ui->setupUi(this);

    init_ui();
}

DateSetDialog::~DateSetDialog()
{
    delete ui;
}

void DateSetDialog::init_ui()
{
    str_date = QDate::currentDate().toString("yyyy-MM-dd");
    ui->spinBox_1->setValue(str_date.left(4).toInt());
    ui->spinBox_2->setValue(str_date.mid(5, 2).toInt());
    ui->spinBox_3->setValue(str_date.right(2).toInt());
}

void DateSetDialog::on_buttonBox_accepted()
{
    int year = ui->spinBox_1->value();
    int month = ui->spinBox_2->value();
    int day = ui->spinBox_3->value();

    QString date;
    date.append(QString::number((double)year, 'f', 0));
    date.append("-");
    date.append(QString::number((double)month, 'f', 0));
    date.append("-");
    date.append(QString::number((double)day, 'f', 0));

    emit currentDateChanged(date);
}
