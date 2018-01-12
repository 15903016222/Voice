#include "ut_detect_setting_widget.h"
#include "ui_ut_detect_setting_widget.h"

UTDetectSettingWidget::UTDetectSettingWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UTDetectSettingWidget)
{
    Q_UNUSED(type);
    ui->setupUi(this);
    connect(ui->modeComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(do_modeComboBox_current_index_changed(int)));
}

UTDetectSettingWidget::~UTDetectSettingWidget()
{
    delete ui;
}

void UTDetectSettingWidget::do_modeComboBox_current_index_changed(int index)
{
    emit current_mode_changed(index);
}
