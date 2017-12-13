#include "angle_properties_widget.h"
#include "ui_angle_properties_widget.h"

#include <QDebug>

AnglePropertiesWidget::AnglePropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnglePropertiesWidget)
{
    ui->setupUi(this);
    hide();
}

AnglePropertiesWidget::~AnglePropertiesWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}
