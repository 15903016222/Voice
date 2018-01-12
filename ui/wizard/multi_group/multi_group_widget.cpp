#include "multi_group_widget.h"
#include "ui_multi_group_widget.h"

#include <QComboBox>
#include <QPushButton>
#include "sub_wizard_setting.h"
#include "group_widget.h"


MultiGroupWidget::MultiGroupWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiGroupWidget),
    m_currentGroup(0)
{
    Q_UNUSED(type);
    ui->setupUi(this);

    m_groupVect << new GroupWidget(GROUP_1, this)
                << new GroupWidget(GROUP_2, this)
                << new GroupWidget(GROUP_3, this)
                << new GroupWidget(GROUP_4, this)
                << new GroupWidget(GROUP_5, this)
                << new GroupWidget(GROUP_6, this)
                << new GroupWidget(GROUP_7, this)
                << new GroupWidget(GROUP_8, this);
    for(int i = (m_groupVect.size() - 1); i >= 0; --i) {
        ui->verticalLayout->insertWidget(1, m_groupVect.at(i));
        connect(m_groupVect.at(i), SIGNAL(setting_clicked(int,int)),
                this, SLOT(do_settingBtn_clicked(int,int)));
    }

    m_groupVect.at(m_currentGroup)->setEnabled(true);
}

MultiGroupWidget::~MultiGroupWidget()
{
    delete ui;
}

void MultiGroupWidget::do_settingBtn_clicked(int model, int index)
{
    if(m_subWizardSetting.isNull()) {
        m_subWizardSetting = QSharedPointer<SubWizardSetting>(new SubWizardSetting());
        connect(m_subWizardSetting.data(), SIGNAL(next_group()), this, SLOT(do_sub_wizard_setting_next_group()));
        connect(m_subWizardSetting.data(), SIGNAL(finished_wizard_setting(WizardSetting::E_WIZARD_TYPE)),
                this, SLOT(do_finished_setting()));
    }

    m_currentGroup = index;

    switch (model) {
        case TOFD:
        {
            m_subWizardSetting->show(WizardSetting::SUB_UT_DETECT);
            break;
        }
        case PE:
        {
            m_subWizardSetting->show(WizardSetting::SUB_UT_DETECT);
            break;
        }
        case PA:
        {
            m_subWizardSetting->show(WizardSetting::SUB_WELD_PA_DETECT);
            break;
        }
        default:
            return;
    }
}

void MultiGroupWidget::do_sub_wizard_setting_next_group()
{
     m_subWizardSetting->hide();

    do_finished_setting();
    if(m_currentGroup >= GROUP_8) {
        return;
    }
    m_groupVect.at(m_currentGroup + 1)->setEnabled(true);
    m_groupVect.at(m_currentGroup + 1)->set_focus();
}

void MultiGroupWidget::do_finished_setting()
{
    m_groupVect.at(m_currentGroup)->set_state(true);
}
