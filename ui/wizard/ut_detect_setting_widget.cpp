#include "ut_detect_setting_widget.h"
#include "ui_ut_detect_setting_widget.h"

#include <QDebug>

UTDetectSettingWidget::UTDetectSettingWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UTDetectSettingWidget)
{
    ui->setupUi(this);

    connect(ui->modeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(do_modeComboBox_current_index_changed(int)));
}

UTDetectSettingWidget::~UTDetectSettingWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}

void UTDetectSettingWidget::do_modeComboBox_current_index_changed(int index)
{
    qDebug() << "[" << __FUNCTION__ << "]" << " index  = " << index;
    emit current_mode_changed(index);
}
