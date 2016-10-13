#include "subnetsetdialog.h"
#include "ui_subnetsetdialog.h"

SubNetSetDialog::SubNetSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubNetSetDialog)
{
    ui->setupUi(this);
    init_ui();

}

SubNetSetDialog::~SubNetSetDialog()
{
    delete ui;
}

void SubNetSetDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void SubNetSetDialog::init_ui()
{
    int subNet_1 = ui->spinBox_1->value();
    int subNet_2 = ui->spinBox_2->value();
    int subNet_3 = ui->spinBox_3->value();
    int subNet_4 = ui->spinBox_4->value();

    str_subNet.clear();
    str_subNet.append(QString::number((double)subNet_1, 'f', 0));
    str_subNet.append(".");
    str_subNet.append(QString::number((double)subNet_2, 'f', 0));
    str_subNet.append(".");
    str_subNet.append(QString::number((double)subNet_3, 'f', 0));
    str_subNet.append(".");
    str_subNet.append(QString::number((double)subNet_4, 'f', 0));
}

void SubNetSetDialog::on_buttonBox_accepted()
{
    init_ui();

    emit currentSubNetChanged(str_subNet);
}
