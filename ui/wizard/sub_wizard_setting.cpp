#include "sub_wizard_setting.h"

#include <QDebug>
#include <QSharedPointer>

#include "selector.h"

SubWizardSetting::SubWizardSetting(QWidget *parent) : WizardSetting(parent)
{
    m_widgetSelector->get_last_widget();
}

void SubWizardSetting::show(WizardSetting::E_WIZARD_TYPE type)
{
    WizardSetting::show(type);

    if((type == SUB_SINGLE_DETECT || type == SUB_WELD_PA_DETECT)) {

        connect(m_widgetSelector->get_last_widget(), SIGNAL(next_group_clicked()), this, SLOT(do_next_group()));
    }
}


void SubWizardSetting::on_backBtn_clicked()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "back clicked";
    WizardSetting::on_backBtn_clicked();
}


void SubWizardSetting::on_nextBtn_clicked()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "next clicked";
    WizardSetting::on_nextBtn_clicked();

}

void SubWizardSetting::do_next_group()
{
    qDebug() << "SubWizardSetting::do_next_group" ;
    hide_step_widget();
    emit next_group();
}
