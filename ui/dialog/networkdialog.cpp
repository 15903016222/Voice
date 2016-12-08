#include "networkdialog.h"
#include "ui_networkdialog.h"

NetworkDialog::NetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void NetworkDialog::on_buttonBox_accepted()
{
    int value_1 = ui->spinBox_1->value();
    int value_2 = ui->spinBox_2->value();
    int value_3 = ui->spinBox_3->value();
    int value_4 = ui->spinBox_4->value();

    if(titleMap.keys().at(0) == "IP Address") {
        str_ip.clear();
        str_ip.append(QString::number((double)value_1, 'f', 0));
        str_ip.append(".");
        str_ip.append(QString::number((double)value_2, 'f', 0));
        str_ip.append(".");
        str_ip.append(QString::number((double)value_3, 'f', 0));
        str_ip.append(".");
        str_ip.append(QString::number((double)value_4, 'f', 0));
    }else{
        str_subNet.clear();
        str_subNet.append(QString::number((double)value_1, 'f', 0));
        str_subNet.append(".");
        str_subNet.append(QString::number((double)value_2, 'f', 0));
        str_subNet.append(".");
        str_subNet.append(QString::number((double)value_3, 'f', 0));
        str_subNet.append(".");
        str_subNet.append(QString::number((double)value_4, 'f', 0));
    }
}

void NetworkDialog::set_dialog_title(QMap<QString, QString> map)
{
    ui->label->setText(map.values().at(0));
    titleMap = map;
}

void NetworkDialog::set_spinbox_value(QList<int> valueList)
{
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
    ui->spinBox_4->setValue(valueList.at(3));
}
