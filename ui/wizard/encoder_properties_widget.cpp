#include "encoder_properties_widget.h"
#include "ui_encoder_properties_widget.h"

#include <QDebug>

EncoderPropertiesWidget::EncoderPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EncoderPropertiesWidget)
{
    ui->setupUi(this);

    hide();
}

EncoderPropertiesWidget::~EncoderPropertiesWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}
