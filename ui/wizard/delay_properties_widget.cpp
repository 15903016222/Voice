#include "delay_properties_widget.h"
#include "ui_delay_properties_widget.h"

#include <QDebug>

DelayPropertiesWidget::DelayPropertiesWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DelayPropertiesWidget)
{
    Q_UNUSED(type);
    ui->setupUi(this);
    hide();
}

DelayPropertiesWidget::~DelayPropertiesWidget()
{
    delete ui;
}
