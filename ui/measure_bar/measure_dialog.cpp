#include "measure_dialog.h"
#include "ui_measure_dialog.h"

MeasureDialog::MeasureDialog(QWidget *parent, MeasureDialog::MeasureType type) :
    QDialog(parent),
    ui(new Ui::MeasureDialog)
{
    ui->setupUi(this);

    setWindowFlags( (windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::FramelessWindowHint);

    ui->listWidget->setCurrentRow(type);
}

MeasureDialog::~MeasureDialog()
{
    delete ui;
}

MeasureDialog::MeasureType MeasureDialog::get_type() const
{
    return (MeasureDialog::MeasureType)ui->listWidget->currentRow();
}

const QString MeasureDialog::get_type_string() const
{
    return ui->listWidget->currentItem()->text();
}

void MeasureDialog::set_type(MeasureDialog::MeasureType type)
{
    ui->listWidget->setCurrentRow(type);
}
