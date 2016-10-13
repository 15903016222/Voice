#include "ipsetdialog.h"
#include "ui_ipsetdialog.h"

IPSetDialog::IPSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IPSetDialog)
{
    ui->setupUi(this);
    init_ui();
}

IPSetDialog::~IPSetDialog()
{
    delete ui;
}

void IPSetDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void IPSetDialog::init_ui()
{
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

void IPSetDialog::on_buttonBox_accepted()
{
    init_ui();
    emit currentIPChanged(str_ip);
}
