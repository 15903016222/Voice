#include "probedialog.h"
#include "ui_probedialog.h"

ProbeDialog::ProbeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProbeDialog)
{
    ui->setupUi(this);
}

ProbeDialog::~ProbeDialog()
{
    delete ui;
}
