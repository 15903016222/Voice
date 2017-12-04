/**
 * @file sub_menu.cpp
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "sub_menu.h"

/* UT Settings */
#include "ut_setting/general_menu.h"
#include "ut_setting/pulser_menu.h"
#include "ut_setting/receiver_menu.h"
#include "ut_setting/ut_advanced_menu.h"

/* Gate/Curves */
#include "gate_curves/gate_menu.h"
#include "gate_curves/alarm_menu.h"
#include "gate_curves/output_menu.h"
#include "gate_curves/analog_menu.h"
#include "gate_curves/dac_menu.h"
#include "gate_curves/tcg_menu.h"

/* Display */
#include "display/display_selection_menu.h"
#include "display/color_setting_menu.h"
#include "display/properties_menu.h"

/* Probe/Part */
#include "probe_part/selection_menu.h"
#include "probe_part/position_menu.h"
#include "probe_part/fft_menu.h"
#include "probe_part/part_menu.h"
#include "probe_part/advanced_menu.h"

/* Focal Law */
#include "focal_law/law_config_menu.h"
#include "focal_law/angle_menu.h"
#include "focal_law/apeture_menu.h"
#include "focal_law/focal_point_menu.h"

/* Scan */
#include "scan/inspection_menu.h"
#include "scan/encoder_menu.h"
#include "scan/area_menu.h"
#include "scan/start_menu.h"

/* Measurement */
#include "measurement/cursors_menu.h"
#include "measurement/tofd_menu.h"
#include "measurement/flaw_record_menu.h"

/* File/Report */
#include "file_report/file_menu.h"
#include "file_report/format_menu.h"
#include "file_report/report_menu.h"
#include "file_report/save_mode_menu.h"
#include "file_report/user_field_menu.h"

/* Preference */
#include "preference/network_menu.h"
#include "preference/preference_menu.h"
#include "preference/system_menu.h"

#include <QDebug>
#include <QEvent>
#include <QKeyEvent>
#include <QGraphicsOpacityEffect>

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    m_curMenu(NULL)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    create_menus();

    set_menu(MainMenu::UTSettings_General);

    set_opacity_main_menu(80);
}

SubMenu::~SubMenu()
{
}

void SubMenu::set_menu(MainMenu::Type type)
{
    if (m_curMenu) {
        m_curMenu->hide();
        m_curMenu->removeEventFilter(this);
    }

    m_curMenu = get_menu(type);

    if(m_curMenu) {
        m_curMenu->installEventFilter(this);
        m_curMenu->show();
    }
}

void SubMenu::set_opacity_main_menu(double value)
{
    QGraphicsOpacityEffect opacityEffect;
    opacityEffect.setOpacity(value / 100);
    this->setGraphicsEffect(&opacityEffect);
}

void SubMenu::create_menus()
{
    /* UT Setting */
    add_menu(MainMenu::UTSettings_General,      new DplUtSettingMenu::GeneralMenu(this));
    add_menu(MainMenu::UTSettings_Pulser,       new DplUtSettingMenu::PulserMenu(this));
    add_menu(MainMenu::UTSettings_Receiver,     new DplUtSettingMenu::ReceiverMenu(this));
    add_menu(MainMenu::UTSettings_Advanced,     new DplUtSettingMenu::UtAdvancedMenu(this));

    /* Gate/Curves */
    add_menu(MainMenu::GateCurves_Gate,         new DplGateCurvesMenu::GateMenu(this));
    add_menu(MainMenu::GateCurves_Alarm,        new DplGateCurvesMenu::AlarmMenu(this));
    add_menu(MainMenu::GateCurves_Output,       new DplGateCurvesMenu::OutputMenu(this));
    add_menu(MainMenu::GateCurves_Analog,       new DplGateCurvesMenu::AnalogMenu(this));
    add_menu(MainMenu::GateCurves_DAC,          new DplGateCurvesMenu::DacMenu(this));
    add_menu(MainMenu::GateCurves_TCG,          new DplGateCurvesMenu::TcgMenu(this));

    /* Display */
    add_menu(MainMenu::Display_Selection,       new DplDisplayMenu::SelectionMenu(this));
    add_menu(MainMenu::Display_ColorSettings,   new DplDisplayMenu::ColorSettingMenu(this));
    add_menu(MainMenu::Displsy_Properties,      new DplDisplayMenu::PropertiesMenu(this));

    /* Probe/Part */
    add_menu(MainMenu::ProbePart_Select,        new DplProbeMenu::SelectionMenu(this));
    add_menu(MainMenu::ProbePart_Position,      new DplProbeMenu::PositionMenu(this));
    add_menu(MainMenu::ProbePart_FFT,           new DplProbeMenu::FftMenu(this));
    add_menu(MainMenu::ProbePart_Part,          new DplProbeMenu::PartMenu(this));
    add_menu(MainMenu::ProbePart_Advanced,      new DplProbeMenu::AdvancedMenu(this));

    /* Focal Law */
    add_menu(MainMenu::FocalLaw_LawConfig,      new DplFocalLawMenu::LawConfigMenu(this));
    add_menu(MainMenu::FocalLaw_Angle,          new DplFocalLawMenu::AngleMenu(this));
    add_menu(MainMenu::FocalLaw_Apeture,        new DplFocalLawMenu::ApetureMenu(this));
    add_menu(MainMenu::FacalLaw_FocalPoint,     new DplFocalLawMenu::FocalPointMenu(this));

    /* Scan */
    add_menu(MainMenu::Scan_Inspection,         new DplScanMenu::InspectionMenu(this));
    add_menu(MainMenu::Scan_Encoder,            new DplScanMenu::EncoderMenu(this));
    add_menu(MainMenu::Scan_Area,               new DplScanMenu::AreaMenu(this));
    add_menu(MainMenu::Scan_Start,              new DplScanMenu::StartMenu(this));

    /* Measurement */
    add_menu(MainMenu::Measurement_Cursors,     new DplMeasurementMenu::CursorsMenu(this));
    add_menu(MainMenu::Measurement_TOFD,        new DplMeasurementMenu::TofdMenu(this));
    add_menu(MainMenu::Measurement_FlawRecord,  new DplMeasurementMenu::FlawRecordMenu(this));

    /* File/Report */
    add_menu(MainMenu::FileReport_File,         new DplFileReportMenu::FileMenu(this));
    add_menu(MainMenu::FileReport_SaveMode,     new DplFileReportMenu::SaveModeMenu(this));
    add_menu(MainMenu::FileReport_Report,       new DplFileReportMenu::ReportMenu(this));
    add_menu(MainMenu::FileReport_Format,       new DplFileReportMenu::FormatMenu(this));
    add_menu(MainMenu::FileReport_UserField,    new DplFileReportMenu::UserFieldMenu(this));

    /* Preference */
    add_menu(MainMenu::Preference_Preference,   new DplPreferenceMenu::PreferenceMenu(this));
    add_menu(MainMenu::Preference_System,       new DplPreferenceMenu::SystemMenu(this));
    add_menu(MainMenu::Preference_Network,      new DplPreferenceMenu::NetworkMenu(this));
}
