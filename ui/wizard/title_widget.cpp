#include "title_widget.h"
#include "ui_title_widget.h"

static QString FIRST_STEP = "://resource/wizard/first_step.png";
static QString SECOND_STEP = "://resource/wizard/second_step.png";
static QString THIRD_STEP = "://resource/wizard/third_step.png";
static QString FOURTH_STEP = "://resource/wizard/fourth_step.png";

static QString UT_FIRST_STEP = "://resource/wizard/ut_first_step.png";
static QString UT_SECOND_STEP = "://resource/wizard/ut_second_step.png";

static QString MULTI_GROUP = "://resource/wizard/multi_group.png";

TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleWidget)
{
    ui->setupUi(this);
    ui->firstWidget->installEventFilter(this);
    ui->secondWidget->installEventFilter(this);
    ui->thirdWidget->installEventFilter(this);
    ui->fourthWidget->installEventFilter(this);
}

TitleWidget::~TitleWidget()
{
    delete ui;
}

void TitleWidget::set_step(int step)
{
    if(step >= m_stepWidgetVect.size() || step < 0) {
        return;
    }

    for(int i = 0; i < m_stepWidgetVect.size(); ++i) {
        if(i <= step) {
            m_stepWidgetVect.at(i)->set_selected(true);
        } else {
            m_stepWidgetVect.at(i)->set_selected(false);
        }
    }
}

void TitleWidget::set_type(WizardSetting::E_WIZARD_TYPE type)
{
    m_type = type;
    switch (type)
    {
        case WizardSetting::WELD_PA_DETECT:
        case WizardSetting::SUB_WELD_PA_DETECT:
        case WizardSetting::COMMON_PA_DETECT:
        {
            ui->firstWidget->show();
            ui->secondWidget->show();
            ui->thirdWidget->show();
            ui->fourthWidget->show();
            m_stepWidgetVect.clear();
            m_stepWidgetVect << ui->firstWidget << ui->secondWidget << ui->thirdWidget << ui->fourthWidget;
            ui->firstWidget->set_title(tr("Probe/Part"));
            ui->secondWidget->set_title(tr("Focallaw"));
            ui->thirdWidget->set_title(tr("Setting"));
            ui->fourthWidget->set_title(tr("Calibration"));
            set_step(WizardSetting::STEP_1);
            break;
        }
        case WizardSetting::MULTI_GROUP_DETECT:
        {
            ui->firstWidget->show();
            ui->secondWidget->hide();
            ui->thirdWidget->hide();
            ui->fourthWidget->hide();
            m_stepWidgetVect.clear();
            m_stepWidgetVect << ui->firstWidget;
            ui->firstWidget->set_title(tr("Multi Group"));
            set_step(WizardSetting::STEP_1);
            break;
        }
        case WizardSetting::UT_DETECT:
        case WizardSetting::SUB_UT_DETECT:
        {
            ui->firstWidget->show();
            ui->secondWidget->show();
            ui->thirdWidget->hide();
            ui->fourthWidget->hide();
            m_stepWidgetVect.clear();
            m_stepWidgetVect << ui->firstWidget << ui->secondWidget;
            ui->firstWidget->set_title(tr("Setting"));
            ui->secondWidget->set_title(tr("Calibration"));
            set_step(WizardSetting::STEP_1);
            break;
        }
        default:
            return;
            break;
    }
}

bool TitleWidget::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonRelease) {
        if(ui->firstWidget == obj) {
            set_step(WizardSetting::STEP_1);
            emit clicked(WizardSetting::STEP_1);
            return true;
        } else if(ui->secondWidget == obj) {
            set_step(WizardSetting::STEP_2);
            emit clicked(WizardSetting::STEP_2);
            return true;
        } else if(ui->thirdWidget == obj) {
            set_step(WizardSetting::STEP_3);
            emit clicked(WizardSetting::STEP_3);
            return true;
        } else if(ui->fourthWidget == obj) {
            set_step(WizardSetting::STEP_4);
            emit clicked(WizardSetting::STEP_4);
            return true;
        }
    }

    return QWidget::eventFilter(obj, e);
}
