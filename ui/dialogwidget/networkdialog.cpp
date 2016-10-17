#include "networkdialog.h"
#include "ui_networkdialog.h"

NetworkDialog::NetworkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkDialog)
{
    ui->setupUi(this);
    init_ui();
}

NetworkDialog::~NetworkDialog()
{
    delete ui;
}

void NetworkDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void NetworkDialog::init_ui()
{
    ui->spinBox_1->setMaximum(255);
    ui->spinBox_2->setMaximum(255);
    ui->spinBox_3->setMaximum(255);
    ui->spinBox_4->setMaximum(255);

    int ip_1 = ui->spinBox_1->value();
    int ip_2 = ui->spinBox_2->value();
    int ip_3 = ui->spinBox_3->value();
    int ip_4 = ui->spinBox_4->value();

    str_ip.clear();
    str_ip.append(QString::number((double)ip_1, 'f', 0));
    str_ip.append(".");
    str_ip.append(QString::number((double)ip_2, 'f', 0));
    str_ip.append(".");
    str_ip.append(QString::number((double)ip_3, 'f', 0));
    str_ip.append(".");
    str_ip.append(QString::number((double)ip_4, 'f', 0));

}

void NetworkDialog::on_buttonBox_accepted()
{
    init_ui();
    emit currentIPChanged(str_ip);
}

void NetworkDialog::set_dialog_title(QString string)
{
    ui->label->setText(string);
}

void NetworkDialog::set_spinbox_value(QList<int> valueList)
{
    ui->spinBox_1->setValue(valueList.at(0));
    ui->spinBox_2->setValue(valueList.at(1));
    ui->spinBox_3->setValue(valueList.at(2));
    ui->spinBox_4->setValue(valueList.at(3));


}
