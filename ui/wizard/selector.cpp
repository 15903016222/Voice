#include "selector.h"

#include <QDebug>

#include "probe_part_widget.h"
#include "focallaw_widget.h"
#include "pa_detect_setting_widget.h"
#include "calibration_widget.h"
#include "multi_group_widget.h"
#include "ut_detect_setting_widget.h"


Selector::Selector(QObject *parent) : QObject(parent),
    m_type(WizardSetting::WELD_PA_DETECT),
    m_currentIndex(-1)
{

}

Selector::~Selector()
{
}


QWidget *Selector::get_current_widget(WizardSetting::E_WIZARD_TYPE type)
{
    if(type == m_type && m_currentIndex != -1) {
        return m_widgetList.at(m_currentIndex);
    }

    clear_widget();

    m_type = type;
    m_currentIndex = 0;

    switch (type)
    {
        case WizardSetting::WELD_PA_DETECT:
        {
            m_widgetList << new ProbePartWidget(type);
            m_widgetList << new FocallawWidget(type);
            m_widgetList << new PADetectSettingWidget(type);
            m_widgetList << new CalibrationWidget(type, false);
            break;
        }
        case WizardSetting::COMMON_PA_DETECT:
        {
            m_widgetList << new ProbePartWidget(type);
            m_widgetList << new FocallawWidget(type);
            m_widgetList << new PADetectSettingWidget(type);
            m_widgetList << new CalibrationWidget(type, false);
            break;
        }
        case WizardSetting::MULTI_GROUP_DETECT:
        {
            m_widgetList << new MultiGroupWidget(type);
            break;
        }
        case WizardSetting::UT_DETECT:
        {
            UTDetectSettingWidget *utDetectSettingWidget    = new UTDetectSettingWidget(type);
            CalibrationWidget     *calibrationWidget        = new CalibrationWidget(type);

            connect(utDetectSettingWidget, SIGNAL(current_mode_changed(int)), calibrationWidget, SLOT(do_utDetectSettingWidget_current_mode_changed(int)));

            m_widgetList << (QWidget*)utDetectSettingWidget ;
            m_widgetList << (QWidget*)calibrationWidget;
            break;
        }
        case WizardSetting::SUB_WELD_PA_DETECT:
        {
            m_widgetList << new ProbePartWidget(type);
            m_widgetList << new FocallawWidget(type);
            m_widgetList << new PADetectSettingWidget(type);
            m_widgetList << new CalibrationWidget(type, true);
            break;
        }
        case WizardSetting::SUB_UT_DETECT:
        {
            UTDetectSettingWidget *utDetectSettingWidget    = new UTDetectSettingWidget(type);
            CalibrationWidget     *calibrationWidget        = new CalibrationWidget(type, true);

            connect(utDetectSettingWidget, SIGNAL(current_mode_changed(int)), calibrationWidget, SLOT(do_utDetectSettingWidget_current_mode_changed(int)));

            m_widgetList << (QWidget*)utDetectSettingWidget ;
            m_widgetList << (QWidget*)calibrationWidget;
            break;
        }
        default:
            return NULL;
            break;
    }

    return m_widgetList.at(m_currentIndex);
}


QWidget *Selector::get_pre_widget()
{
    if(m_widgetList.at(m_currentIndex) == m_widgetList.back()) {
        return NULL;
    } else {
        QWidget *preWidget = m_widgetList.at(++m_currentIndex);
        return preWidget;
    }
}


QWidget *Selector::get_back_widget()
{
    if(m_widgetList.first() == m_widgetList.at(m_currentIndex)) {
        return NULL;
    } else {
        QWidget *backWidget = m_widgetList.at(--m_currentIndex);
        return backWidget;
    }
}

QWidget *Selector::get_last_widget()
{
    if(m_widgetList.count() == 0) {
        return NULL;
    }

    return m_widgetList.at(m_widgetList.count() - 1);
}


bool Selector::is_last_widget()
{
    if(m_widgetList.size() == 0) {
        return true;
    }

    if(m_currentIndex == (m_widgetList.count() - 1)) {
        return true;
    }else {
        return false;
    }
}

bool Selector::is_first_widget()
{
    if(m_currentIndex == 0) {
        return true;
    } else {
        return false;
    }
}


int Selector::get_current_index()
{
    return m_currentIndex;
}

bool Selector::set_current_index(int index)
{
    if(index >= m_widgetList.count() || index < 0) {
        return false;
    }

    m_currentIndex = index;

    for(int i = 0; i < m_widgetList.count(); ++i) {
        if(i == index) {
            continue;
        }

        m_widgetList.at(i)->hide();
    }
    return true;
}


void Selector::clear_widget()
{
    QList<QWidget*>::iterator it = m_widgetList.begin();
    while(it != m_widgetList.end()) {
        delete (*it);
        ++it;
    }

    m_widgetList.clear();
}
