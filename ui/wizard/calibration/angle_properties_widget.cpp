#include "angle_properties_widget.h"
#include "ui_angle_properties_widget.h"

#include <QDebug>

AnglePropertiesWidget::AnglePropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnglePropertiesWidget)
{
    ui->setupUi(this);
    hide();
    if(parent != NULL) {
        ui->startLabel->setFont(QFont(this->font().family(), 15));
        ui->startLabel->setMinimumHeight(30);
    }
}

AnglePropertiesWidget::~AnglePropertiesWidget()
{
    delete ui;
}
