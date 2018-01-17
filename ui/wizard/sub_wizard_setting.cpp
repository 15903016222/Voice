#include "sub_wizard_setting.h"
#include "ui_wizard_setting.h"
#include <QSharedPointer>
#include "selector.h"

SubWizardSetting::SubWizardSetting(QWidget *parent) : WizardSetting(parent)
{
    m_widgetSelector->get_last_widget();
}

void SubWizardSetting::show(WizardSetting::E_WIZARD_TYPE type)
{
    WizardSetting::show(type);

    if((type == SUB_UT_DETECT || type == SUB_WELD_PA_DETECT)) {
        connect(m_widgetSelector->get_last_widget(), SIGNAL(next_group_clicked()),
                this, SLOT(do_next_group()));
    }
}


void SubWizardSetting::on_backBtn_clicked()
{
    WizardSetting::on_backBtn_clicked();
}


void SubWizardSetting::on_nextBtn_clicked()
{
    if(m_widgetSelector->is_last_widget()) {
        emit next_group();
        return;
    }
    WizardSetting::on_nextBtn_clicked();
}

void SubWizardSetting::do_next_group()
{
    emit next_group();
}