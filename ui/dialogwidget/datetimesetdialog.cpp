#include "datetimesetdialog.h"
#include "ui_datetimesetdialog.h"

#include <QDate>

DateTimeSetDialog::DateTimeSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DateTimeSetDialog)
{
    ui->setupUi(this);

    init_ui();
}

DateTimeSetDialog::~DateTimeSetDialog()
{
    delete ui;
}

void DateTimeSetDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void DateTimeSetDialog::init_ui()
{

}

void DateTimeSetDialog::on_buttonBox_accepted()
{    
    int valueOne = ui->spinBox_1->value();
    int valueTwo = ui->spinBox_2->value();
    int valueThree = ui->spinBox_3->value();

    if(titleMap.keys().at(0) == "Date Set") {
        str_date.clear();
        str_date.append(QString::number((double)valueOne, 'f', 0));
        str_date.append("-");
        str_date.append(QString::number((double)valueTwo, 'f', 0));
        str_date.append("-");
        str_date.append(QString::number((double)valueThree, 'f', 0));

        emit currentDateTimeChanged(str_date);
    } else {
        str_time.clear();
        str_time.append(QString::number((double)valueOne, 'f', 0));
        str_time.append(":");
        str_time.append(QString::number((double)valueTwo, 'f', 0));
        str_time.append(":");
        str_time.append(QString::number((double)valueThree, 'f', 0));

        emit currentDateTimeChanged(str_time);
    }
}

void DateTimeSetDialog::check_date_valid(int number)
{
    Q_UNUSED(number);
    QDate date = QDate(ui->spinBox_1->value(), ui->spinBox_2->value(), ui->spinBox_3->value());
    if(date.isValid()) {
        return;
    } else {
        int days = QDate(ui->spinBox_1->value(), ui->spinBox_2->value(),1).daysInMonth();
        if(ui->spinBox_3->value() > days) {
            ui->spinBox_3->setValue(days);
        }
    }
}

void DateTimeSetDialog::set_dialog_title(QMap<QString, QString> map)
{
    ui->label->setText(map.values().at(0));
    titleMap = map;
    if(map.keys().at(0) == "Date Set") {
        ui->spinBox_1->setMinimum(1970);
        ui->spinBox_2->setMinimum(1);
        ui->spinBox_3->setMinimum(1);

        ui->spinBox_1->setMaximum(5000);
        ui->spinBox_2->setMaximum(12);
        ui->spinBox_3->setMaximum(31);

        connect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
    } else {
        ui->spinBox_1->setMinimum(0);
        ui->spinBox_2->setMinimum(0);
        ui->spinBox_3->setMinimum(0);

        ui->spinBox_1->setMaximum(23);
        ui->spinBox_2->setMaximum(59);
        ui->spinBox_3->setMaximum(59);

        disconnect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        disconnect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
        disconnect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(check_date_valid(int)));
    }
}

void DateTimeSetDialog::set_spinbox_value(QList<int> valueList)
{
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
}
