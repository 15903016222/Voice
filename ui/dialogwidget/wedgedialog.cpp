#include "wedgedialog.h"
#include "ui_wedgedialog.h"

WedgeDialog::WedgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WedgeDialog)
{
    ui->setupUi(this);
    setWindowTitle("Wedge Choice Dialog");
}

WedgeDialog::~WedgeDialog()
{
    delete ui;
}
