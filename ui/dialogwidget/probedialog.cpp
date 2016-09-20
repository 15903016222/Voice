#include "probedialog.h"
#include "ui_probedialog.h"

ProbeDialog::ProbeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProbeDialog)
{
    ui->setupUi(this);
    setWindowTitle("Probe Choice Dialog");
}

ProbeDialog::~ProbeDialog()
{
    delete ui;
}
