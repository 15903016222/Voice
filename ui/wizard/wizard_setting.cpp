#include "wizard_setting.h"

#include "ui_wizard_setting.h"
#include "step_widget.h"
#include "selector.h"

WizardSetting::WizardSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WizardSetting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->settingVerticalLayout->removeWidget(ui->settingWidget);
    ui->settingWidget->hide();

    m_widgetSelector = QSharedPointer<Selector>(new Selector);
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

        update_step_widget(true, currentWidget);
    }
}


void WizardSetting::on_nextBtn_clicked()
{
    if(m_widgetSelector->is_last_widget()) {
        /* 配置完成 */
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
            update_step_widget(false, preWidget);
        }
    }
}

void WizardSetting::do_next_group()
{

}

void WizardSetting::hide_step_widget()
{
    ui->firstWidget->hide();
    ui->secondWidget->hide();
    ui->thirdWidget->hide();
    ui->fourthWidget->hide();
}


void WizardSetting::init_widget()
{
    m_stepWidgetList.clear();

    QWidget *current = NULL;

    if(m_widgetSelector->get_current_index() == 0) {
        current = m_widgetSelector->get_current_widget(m_type);
    } else {

        m_widgetSelector->set_current_index(0);
        current = m_widgetSelector->get_current_widget(m_type);
    }

    ui->nextBtn->show();
    ui->backBtn->show();

    /* 配置步骤显示 */
    switch (m_type)
    {
        case WELD_PA_DETECT:
        case SUB_WELD_PA_DETECT:
        {
            ui->firstWidget->set_widget(StepWidget::WORKPIECE_PROBE, StepWidget::SELECTED);
            ui->secondWidget->set_widget(StepWidget::FOCALLAW, StepWidget::UNSELECTED);
            ui->thirdWidget->set_widget(StepWidget::DETECT_SETTING, StepWidget::UNSELECTED);
            ui->fourthWidget->set_widget(StepWidget::CALIBRATION, StepWidget::UNSELECTED);

            ui->nextBtn->setText(tr("Next"));

            ui->firstWidget->show();
            ui->secondWidget->show();
            ui->thirdWidget->show();
            ui->fourthWidget->show();

            m_stepWidgetList << ui->firstWidget << ui->secondWidget << ui->thirdWidget << ui->fourthWidget;

            break;
        }
        case CURRENT_PA_DETECT:
        {
            ui->firstWidget->set_widget(StepWidget::WORKPIECE_PROBE, StepWidget::SELECTED);
            ui->secondWidget->set_widget(StepWidget::FOCALLAW, StepWidget::UNSELECTED);
            ui->thirdWidget->set_widget(StepWidget::DETECT_SETTING, StepWidget::UNSELECTED);
            ui->fourthWidget->set_widget(StepWidget::CALIBRATION, StepWidget::UNSELECTED);

            ui->firstWidget->show();
            ui->secondWidget->show();
            ui->thirdWidget->show();
            ui->fourthWidget->show();

            ui->nextBtn->setText(tr("Next"));

            m_stepWidgetList << ui->firstWidget << ui->secondWidget << ui->thirdWidget << ui->fourthWidget;

            break;
        }
        case MULTI_GROUP_DETECT:
        {
            ui->firstWidget->set_widget(StepWidget::MULTI_GROUP, StepWidget::SELECTED);

            ui->firstWidget->show();
            ui->secondWidget->hide();
            ui->thirdWidget->hide();
            ui->fourthWidget->hide();

            ui->nextBtn->setText(tr("Finished"));

            m_stepWidgetList << ui->firstWidget;

            break;
        }
        case SINGLE_DETECT:
        case SUB_SINGLE_DETECT:
        {
            ui->firstWidget->set_widget(StepWidget::DETECT_SETTING, StepWidget::SELECTED);
            ui->secondWidget->set_widget(StepWidget::CALIBRATION, StepWidget::UNSELECTED);

            ui->firstWidget->show();
            ui->secondWidget->show();
            ui->thirdWidget->hide();
            ui->fourthWidget->hide();

            ui->nextBtn->setText(tr("Next"));

            m_stepWidgetList << ui->firstWidget << ui->secondWidget;

            break;
        }
        default:
            return;
            break;
    }


    current->show();
    ui->settingVerticalLayout->insertWidget(0, current);
}


void WizardSetting::update_step_widget(bool isBack, QWidget *currentWidget)
{
    int index = m_widgetSelector->get_current_index();
    m_stepWidgetList.at(index)->set_selected(StepWidget::SELECTED);

    if(isBack) {

        if(((WELD_PA_DETECT == m_type || CURRENT_PA_DETECT == m_type || SUB_WELD_PA_DETECT) && (STEP_3 == index))
                || ((SINGLE_DETECT == m_type || SUB_SINGLE_DETECT == m_type) && STEP_1 == index)) {

            ui->backBtn->setHidden(false);
            ui->nextBtn->setHidden(false);

            disconnect(currentWidget, SIGNAL(back_clicked()), this, SLOT(on_backBtn_clicked()));
            disconnect(currentWidget, SIGNAL(finished_clicked()), this, SLOT(on_nextBtn_clicked()));
        }

        m_stepWidgetList.at(++index)->set_selected(StepWidget::UNSELECTED);
        ui->nextBtn->setText(tr("Next"));

    } else {

        if(((WELD_PA_DETECT == m_type || CURRENT_PA_DETECT == m_type || SUB_WELD_PA_DETECT) && (STEP_4 == index))
                || ((SINGLE_DETECT == m_type || SUB_SINGLE_DETECT == m_type) && STEP_2 == index)) {

            ui->backBtn->setHidden(true);
            ui->nextBtn->setHidden(true);
            ui->horizontalSpacer->changeSize(ui->horizontalSpacer->geometry().width(), 0);
            ui->horizontalSpacer_2->changeSize(ui->horizontalSpacer_2->geometry().width(), 0);

            connect(currentWidget, SIGNAL(back_clicked()), this, SLOT(on_backBtn_clicked()));
            connect(currentWidget, SIGNAL(finished_clicked()), this, SLOT(on_nextBtn_clicked()));
        }
    }
}
