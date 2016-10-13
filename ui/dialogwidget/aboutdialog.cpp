#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "creditsdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::retranslate_dialog_ui()
{
    ui->retranslateUi(this);
}

void AboutDialog::on_pushButton_credits_clicked()
{
    CreditsDialog *creditsDialog = new CreditsDialog(this);
    creditsDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    creditsDialog->show();
}
