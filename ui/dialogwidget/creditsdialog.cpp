#include "creditsdialog.h"
#include "ui_creditsdialog.h"

CreditsDialog::CreditsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditsDialog)
{
    ui->setupUi(this);

    ui->tabWidget->removeTab(1);
}

CreditsDialog::~CreditsDialog()
{
    delete ui;
}

void CreditsDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}
