#include "sound_velocity_properties_widget.h"
#include "ui_sound_velocity_properties_widget.h"

#include <QDebug>

SoundVelocityPropertiesWidget::SoundVelocityPropertiesWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SoundVelocityPropertiesWidget)
{
    ui->setupUi(this);
    hide();

    if(type == WizardSetting::SINGLE_DETECT) {
        ui->angleLabel->setHidden(true);
        ui->angleDoubleSpinBox->setHidden(true);
    }
}

SoundVelocityPropertiesWidget::~SoundVelocityPropertiesWidget()
{
    delete ui;
}
