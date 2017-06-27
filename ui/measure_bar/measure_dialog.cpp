#include "measure_dialog.h"
#include "ui_measure_dialog.h"

#include <device/device.h>
#include <device/group.h>

#include <QKeyEvent>

#include <QDebug>

MeasureDialog::MeasureDialog(QWidget *parent, Measure::Type type) :
    QDialog(parent),
    ui(new Ui::MeasureDialog)
{
    ui->setupUi(this);

    setWindowFlags( (windowFlags() & ~Qt::WindowContextHelpButtonHint) | Qt::FramelessWindowHint);

    ui->tableWidget->setCurrentCell(type, 0);
    ui->tableWidget->setColumnHidden(1, true);
}

MeasureDialog::~MeasureDialog()
{
    delete ui;
}

Measure::Type MeasureDialog::get_type() const
{
    return static_cast<Measure::Type>(ui->tableWidget->currentRow());
}

QString MeasureDialog::get_type_string()
{
    return ui->tableWidget->verticalHeaderItem(ui->tableWidget->currentRow())->text();
}

void MeasureDialog::set_type(Measure::Type type)
{
    ui->tableWidget->setCurrentCell(type, 0);
}

void MeasureDialog::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Enter
            || e->key() == Qt::Key_Return) {
        accept();
        return;
    }
    QDialog::keyPressEvent(e);
}

QString MeasureDialog::get_unit() const
{    
    int row = ui->tableWidget->currentRow();
    return ui->tableWidget->item(row, 1)->text();
}
