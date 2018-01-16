#include "title_widget.h"
#include "ui_title_widget.h"

static QString FIRST_SELECTED = "://resource/wizard/first_selected.png";
static QString SECOND_SELECTED = "://resource/wizard/second_selected.png";
static QString SECOND_UNSELECTED = "://resource/wizard/second_unselected.png";
static QString THIRD_SELECTED = "://resource/wizard/third_selected.png";
static QString THIRD_UNSELECTED = "://resource/wizard/third_unselected.png";
static QString FOURTH_SELECTED = "://resource/wizard/fourth_selected.png";
static QString FOURTH_UNSELECTED = "://resource/wizard/fourth_unselected.png";

static QString UT_FIRST_SELECTED = "://resource/wizard/ut_first_selected.png";
static QString UT_SECOND_SELECTED = "://resource/wizard/ut_second_selected.png";
static QString UT_SECOND_UNSELECTED = "://resource/wizard/ut_second_unselected.png";

static QString MULTI_GROUP_SELECTED = "://resource/wizard/multi_group_selected.png";

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
            QStringList list;
            list << FIRST_SELECTED << FIRST_SELECTED;
            ui->firstWidget->set_back_ground(list);
            list.clear();
            list << SECOND_UNSELECTED << SECOND_SELECTED;
            ui->secondWidget->set_back_ground(list);
            list.clear();
            list << THIRD_UNSELECTED << THIRD_SELECTED;
            ui->thirdWidget->set_back_ground(list);
            list.clear();
            list << FOURTH_UNSELECTED << FOURTH_SELECTED;
            ui->fourthWidget->set_back_ground(list);

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
            QStringList list;
            list << MULTI_GROUP_SELECTED << MULTI_GROUP_SELECTED;
            ui->firstWidget->set_back_ground(list);
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
            QStringList list;
            list << UT_FIRST_SELECTED << UT_FIRST_SELECTED;
            ui->firstWidget->set_back_ground(list);
            list.clear();
            list << UT_SECOND_UNSELECTED << UT_SECOND_SELECTED;
            ui->secondWidget->set_back_ground(list);
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
