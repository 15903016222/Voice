#include "wizard_setting.h"

#include "ui_wizard_setting.h"
#include "step_widget.h"
#include "selector.h"

#include <QDebug>

WizardSetting::WizardSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WizardSetting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->settingVerticalLayout->removeWidget(ui->settingWidget);
    ui->settingWidget->hide();

    m_widgetSelector = QSharedPointer<Selector>(new Selector);

    connect(ui->titleWidget, SIGNAL(clicked(int)), this, SLOT(do_step_widget_clicked(int)));
}


WizardSetting::~WizardSetting()
{
    m_widgetSelector->clear_widget();
    delete ui;
}


void WizardSetting::show(WizardSetting::E_WIZARD_TYPE type)
{
    m_type = type;
    init_widget();
    QWidget::show();
}


void WizardSetting::on_backBtn_clicked()
{
    QWidget *currentWidget = m_widgetSelector->get_current_widget(m_type);
    QWidget *backWidget = m_widgetSelector->get_back_widget();

    if(NULL == backWidget) {
        emit cancle_wizard_setting();
        ui->settingVerticalLayout->removeWidget(currentWidget);
        hide();
    } else {
        ui->settingVerticalLayout->insertWidget(0, backWidget);
        ui->settingVerticalLayout->removeWidget(currentWidget);
        currentWidget->hide();
        backWidget->show();
        update_step_widget();
    }
}


void WizardSetting::on_nextBtn_clicked()
{
    if(m_widgetSelector->is_last_widget()) {
        emit finished_wizard_setting(m_type);
        m_widgetSelector->get_current_widget(m_type)->hide();
        ui->settingVerticalLayout->removeWidget(m_widgetSelector->get_current_widget(m_type));
        hide();
    } else {

        QWidget *currentWidget = m_widgetSelector->get_current_widget(m_type);
        QWidget *preWidget = m_widgetSelector->get_pre_widget();

        if(NULL == preWidget) {
            emit finished_wizard_setting(m_type);
            ui->verticalLayout_wizardSetting->removeWidget(currentWidget);
            close();
        } else {
            ui->settingVerticalLayout->removeWidget(currentWidget);
            ui->settingVerticalLayout->insertWidget(0, preWidget);
            preWidget->show();
            currentWidget->hide();
            update_step_widget();
        }
    }
}

void WizardSetting::do_step_widget_clicked(int step)
{
    int currentIndex = m_widgetSelector->get_current_index();
    if(currentIndex == step) {
        return;
    }

    QWidget *currentWidget = m_widgetSelector->get_current_widget(m_type);
    QWidget *targetWidget = m_widgetSelector->get_widget(step);

    ui->settingVerticalLayout->removeWidget(currentWidget);
    ui->settingVerticalLayout->insertWidget(0, targetWidget);

    targetWidget->show();
    currentWidget->hide();
    update_step_widget();
}


void WizardSetting::init_widget()
{
    QWidget *current = NULL;

    if(m_widgetSelector->get_current_index() == 0) {
        current = m_widgetSelector->get_current_widget(m_type);
    } else {
        m_widgetSelector->set_current_index(0);
        current = m_widgetSelector->get_current_widget(m_type);
    }

    ui->nextBtn->show();
    ui->backBtn->show();

    ui->titleWidget->set_type(m_type);
    ui->titleWidget->set_step(STEP_1);

    if(m_type == MULTI_GROUP_DETECT) {
        ui->nextBtn->setText(tr("Finished"));
    } else {
        ui->nextBtn->setText(tr("Next"));
    }

    current->show();
    ui->settingVerticalLayout->insertWidget(0, current);
}


void WizardSetting::update_step_widget()
{
    int index = m_widgetSelector->get_current_index();
    ui->titleWidget->set_step(index);

    if(((WELD_PA_DETECT == m_type || COMMON_PA_DETECT == m_type || SUB_WELD_PA_DETECT) && (STEP_4 == index))
            || ((UT_DETECT == m_type || SUB_UT_DETECT == m_type) && STEP_2 == index)) {

        ui->nextBtn->setText(tr("Finished"));
    } else {
        ui->nextBtn->setText(tr("Next"));
    }
}
