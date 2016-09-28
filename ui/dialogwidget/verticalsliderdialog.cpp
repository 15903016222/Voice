#include "verticalsliderdialog.h"
#include "ui_verticalsliderdialog.h"


VerticalSliderDialog::VerticalSliderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VerticalSliderDialog)
{
    ui->setupUi(this);
    slider.append(ui->sliderBrightness);
}

VerticalSliderDialog::~VerticalSliderDialog()
{
    delete ui;
}

void VerticalSliderDialog::setBrightValue(QString string)
{
    int value = string.toInt();
    ui->sliderBrightness->setValue(value);
}

void VerticalSliderDialog::on_pushButton_add_clicked()
{
    int i = ui->sliderBrightness->value();
    i = i + 10;
    ui->sliderBrightness->setValue(i);
}

void VerticalSliderDialog::on_pushButton_decrease_clicked()
{
    int i = ui->sliderBrightness->value();
    i = i - 10;
    ui->sliderBrightness->setValue(i);
}
