#include "verticalsliderdialog.h"
#include "ui_verticalsliderdialog.h"


VerticalSliderDialog::VerticalSliderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerticalSliderDialog)
{
    ui->setupUi(this);
    slider.append(ui->verticalSlider);
}

VerticalSliderDialog::~VerticalSliderDialog()
{
    delete ui;
}

void VerticalSliderDialog::setBrightValue(QString string)
{
    int value = string.toInt();
    ui->verticalSlider->setValue(value);
}

void VerticalSliderDialog::on_pushButton_1_clicked()
{
    int i = ui->verticalSlider->value();
    i = i + 10;
    ui->verticalSlider->setValue(i);
}

void VerticalSliderDialog::on_pushButton_2_clicked()
{
    int i = ui->verticalSlider->value();
    i = i - 10;
    ui->verticalSlider->setValue(i);
}
