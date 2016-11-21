#include "measure_dialog.h"
#include "ui_measure_dialog.h"

MeasureDialog::MeasureDialog(QWidget *parent, MeasureDialog::MeasureType type) :
    QDialog(parent),
    ui(new Ui::MeasureDialog)
{
    ui->setupUi(this);

    setWindowFlags( (windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::FramelessWindowHint);

    ui->tableWidget->setCurrentCell(type, 0);
}

MeasureDialog::~MeasureDialog()
{
    delete ui;
}

MeasureDialog::MeasureType MeasureDialog::get_type() const
{
    return (MeasureDialog::MeasureType)ui->tableWidget->currentRow();
}

QString MeasureDialog::get_type_string()
{
    return ui->tableWidget->verticalHeaderItem(ui->tableWidget->currentRow())->text();
}

void MeasureDialog::set_type(MeasureDialog::MeasureType type)
{
    ui->tableWidget->setCurrentCell(type, 0);
}
