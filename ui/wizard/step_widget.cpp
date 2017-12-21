#include "step_widget.h"
#include "ui_step_widget.h"

#include <QPainter>
#include <QDebug>

static QString g_workPieceOn        = ":/resources/wizard/workpiece_probe_selected.png";
static QString g_workPieceOff       = ":/resources/wizard/workpiece_probe_unselected.png";
static QString g_focallawOn         = ":/resources/wizard/focallow_selected.png";
static QString g_focallawOff        = ":/resources/wizard/focallow_unselected.png";
static QString g_calibrationOn      = ":/resources/wizard/caribation_selected.png";
static QString g_calibrationOff     = ":/resources/wizard/calibration_unselected.png";
static QString g_detectSettingOn    = ":/resources/wizard/detect_setting_selected.png";
static QString g_detectSettingOff   = ":/resources/wizard/detect_setting_unselected.png";
static QString g_multiGroupOn       = ":/resources/wizard/multi_group_selected.png";
static QString g_multiGroupOff      = ":/resources/wizard/multi_group_unselected.png";

StepWidget::StepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepWidget)
{
    ui->setupUi(this);

    m_type = UNSELECTED;
    select_pic(WORKPIECE_PROBE);
}

StepWidget::~StepWidget()
{
    delete ui;
}

void StepWidget::set_widget(StepWidget::E_STEP_TYPE stepType, StepWidget::E_SELECT_TYPE selectType)
{
    select_pic(stepType);
    m_type = selectType;
    repaint();
    show();
}

void StepWidget::set_selected(StepWidget::E_SELECT_TYPE type)
{
    if(type == m_type)
    {
        return;
    }

    m_type = type;
    repaint();
}


void StepWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    if(!m_pic.isEmpty()) {
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawPixmap(rect(), QPixmap(m_pic.at(m_type)));
    } else {
        setStyleSheet("background-color: rgb(0, 127, 255)");
    }

}

void StepWidget::select_pic(StepWidget::E_STEP_TYPE type)
{
    m_pic.clear();

    switch (type) {
        case WORKPIECE_PROBE:
        {
            m_pic << g_workPieceOff << g_workPieceOn;
            break;
        }
        case FOCALLAW:
        {
            m_pic << g_focallawOff << g_focallawOn;
            break;
        }
        case CALIBRATION:
        {
            m_pic << g_calibrationOff << g_calibrationOn;
            break;
        }
        case DETECT_SETTING:
        {
            m_pic << g_detectSettingOff << g_detectSettingOn;
            break;
        }
        case MULTI_GROUP:
        {
            m_pic << g_multiGroupOff << g_multiGroupOn;
            break;
        }
        default:
             m_pic << g_workPieceOff << g_workPieceOn;
            break;
    }
}


