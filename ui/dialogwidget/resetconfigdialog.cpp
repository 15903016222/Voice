#include "resetconfigdialog.h"
#include "ui_resetconfigdialog.h"

ResetConfigDialog::ResetConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetConfigDialog)
{
    ui->setupUi(this);
}

ResetConfigDialog::~ResetConfigDialog()
{
    delete ui;
}

void ResetConfigDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}
