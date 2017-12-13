#include "multi_group_widget.h"
#include "ui_multi_group_widget.h"

#include <QDebug>
#include <QMessageBox>
#include "sub_wizard_setting.h"


MultiGroupWidget::MultiGroupWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiGroupWidget)
{
    ui->setupUi(this);

    connect(ui->settingBtn1, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));
    connect(ui->settingBtn2, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));
    connect(ui->settingBtn3, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));
    connect(ui->settingBtn4, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));
    connect(ui->settingBtn5, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));
    connect(ui->settingBtn6, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));
    connect(ui->settingBtn7, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));
    connect(ui->settingBtn8, SIGNAL(clicked(bool)), this, SLOT(do_settingBtn_clicked()));

    m_pushButtonComboBoxMap.insert(ui->settingBtn1, ui->settingComboBox1);
    m_pushButtonComboBoxMap.insert(ui->settingBtn2, ui->settingComboBox2);
    m_pushButtonComboBoxMap.insert(ui->settingBtn3, ui->settingComboBox3);
    m_pushButtonComboBoxMap.insert(ui->settingBtn4, ui->settingComboBox4);
    m_pushButtonComboBoxMap.insert(ui->settingBtn5, ui->settingComboBox5);
    m_pushButtonComboBoxMap.insert(ui->settingBtn6, ui->settingComboBox6);
    m_pushButtonComboBoxMap.insert(ui->settingBtn7, ui->settingComboBox7);
    m_pushButtonComboBoxMap.insert(ui->settingBtn8, ui->settingComboBox8);

    m_groupNOComboBoxMap.insert(GROUP_1, ui->settingComboBox1);
    m_groupNOComboBoxMap.insert(GROUP_2, ui->settingComboBox2);
    m_groupNOComboBoxMap.insert(GROUP_3, ui->settingComboBox3);
    m_groupNOComboBoxMap.insert(GROUP_4, ui->settingComboBox4);
    m_groupNOComboBoxMap.insert(GROUP_5, ui->settingComboBox5);
    m_groupNOComboBoxMap.insert(GROUP_6, ui->settingComboBox6);
    m_groupNOComboBoxMap.insert(GROUP_7, ui->settingComboBox7);
    m_groupNOComboBoxMap.insert(GROUP_8, ui->settingComboBox8);


}

MultiGroupWidget::~MultiGroupWidget()
{
    qDebug()<< "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}


void MultiGroupWidget::do_settingBtn_clicked()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "do_settingBtn_clicked";

    QPushButton *current = qobject_cast<QPushButton*> (sender());

    if(NULL == current) {
        return;
    }

    if(m_subWizardSetting.isNull()) {
        m_subWizardSetting = QSharedPointer<SubWizardSetting>(new SubWizardSetting());
        connect(m_subWizardSetting.data(), SIGNAL(next_group()), this, SLOT(do_sub_wizard_setting_next_group()));
    }

    m_currentGroup = m_groupNOComboBoxMap.key(m_pushButtonComboBoxMap.value(current));

    switch (m_pushButtonComboBoxMap.value(current)->currentIndex()) {
        case NA:
        {
            QMessageBox::warning(this, tr("Warnning"), tr("please select model."));
            m_pushButtonComboBoxMap.value(current)->setFocus();
            return;
            break;
        }
        case TOFD:
        {
            m_subWizardSetting->show(WizardSetting::SUB_SINGLE_DETECT);
            break;
        }
        case PE:
        {
            m_subWizardSetting->show(WizardSetting::SUB_SINGLE_DETECT);
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
    qDebug()<< "[" << __FUNCTION__ << "]" << "do_sub_wizard_setting_next_group";

    if(m_currentGroup >= GROUP_8) {
        m_subWizardSetting->hide();
        return;
    }

    m_currentGroup++;

    if(m_groupNOComboBoxMap.value((E_GROUP_NO)m_currentGroup)->currentIndex() == NA) {

        m_subWizardSetting->hide();
        m_groupNOComboBoxMap.value((E_GROUP_NO)m_currentGroup)->setFocus();

    } else {

        switch (m_groupNOComboBoxMap.value((E_GROUP_NO)m_currentGroup)->currentIndex()) {
            case TOFD:
            {
                m_subWizardSetting->show(WizardSetting::SUB_SINGLE_DETECT);
                break;
            }
            case PE:
            {
                m_subWizardSetting->show(WizardSetting::SUB_SINGLE_DETECT);
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
}


