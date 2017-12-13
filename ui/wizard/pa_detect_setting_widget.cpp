#include "pa_detect_setting_widget.h"

#include <QDebug>
#include "ui_pa_detect_setting_widget.h"

PADetectSettingWidget::PADetectSettingWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PADetectSettingWidget)
{
    ui->setupUi(this);

    connect(ui->oneLineCheckBox, SIGNAL(pressed()), this, SLOT(do_checkBox_pressed()));
    connect(ui->rasterCheckBox, SIGNAL(pressed()), this, SLOT(do_checkBox_pressed()));

}

PADetectSettingWidget::~PADetectSettingWidget()
{
    qDebug()<< "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}

void PADetectSettingWidget::do_checkBox_pressed()
{
    QCheckBox *current = qobject_cast<QCheckBox*> (sender());
    if(current == NULL) {
        return;
    }

    if(current->objectName() == ui->oneLineCheckBox->objectName()) {
        ui->rasterCheckBox->setChecked(false);
    } else if(current->objectName() == ui->rasterCheckBox->objectName()) {
        ui->oneLineCheckBox->setChecked(false);
    }
}
