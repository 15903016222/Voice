#include "measure_dialog.h"
#include "ui_measure_dialog.h"

#include <device/device.h>
#include <device/group.h>

#include <QKeyEvent>

#include <QDebug>

MeasureDialog::MeasureDialog(QWidget *parent, MeasureDialog::MeasureType type) :
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
    if(DplDevice::Device::get_instance()->current_group()->ut_unit() == DplDevice::Group::Time && row >= 6 && row <= 9) {
        return QString("&micro;s");
    } else {
        return ui->tableWidget->item(row, 1)->text();
    }

}
