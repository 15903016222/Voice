#include "common_setting_widget.h"
#include "ui_common_setting_widget.h"

#include <QDebug>

CommonSettingWidget::CommonSettingWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    m_type(type),
    m_mode(TOFD)
{

}

CommonSettingWidget::~CommonSettingWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << " destructor." << m_type;
}

void CommonSettingWidget::set_mode(CommonSettingWidget::E_DETECT_MODE mode)
{
    if(WizardSetting::SINGLE_DETECT != m_type
            || mode == m_mode) {
        return;
    }

    m_mode = mode;

    initModeWidget();
}

void CommonSettingWidget::initModeWidget()
{

}
