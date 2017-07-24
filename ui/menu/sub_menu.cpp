/**
 * @file sub_menu.cpp
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "sub_menu.h"

#include <QVBoxLayout>

/* UT Settings */
#include "ut_setting/general_menu.h"
#include "ut_setting/pulser_menu.h"
#include "ut_setting/receiver_menu.h"
#include "ut_setting/ut_advanced_menu.h"

/* Gate/Curves */
#include "gate_curves/gate_menu.h"
#include "gate_curves/alarm_menu.h"
#include "gate_curves/output_menu.h"
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


SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    m_curMenu(NULL)
{
    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);

    init_map();

    set_menu(MainMenu::UTSettings_General);

    m_opacityEffect = new QGraphicsOpacityEffect;
    set_opacity_main_menu(80);
}

void SubMenu::init_map()
{
    QTime time;
    time.restart();
    /* UT Setting */
    m_funMap.insert(MainMenu::UTSettings_General,       &SubMenu::create_general_menu);
    m_funMap.insert(MainMenu::UTSettings_Pulser,        &SubMenu::create_pulser_menu);
    m_funMap.insert(MainMenu::UTSettings_Receiver,      &SubMenu::create_receiver_menu);
    m_funMap.insert(MainMenu::UTSettings_Advanced,      &SubMenu::create_utadvanced_menu);
    qDebug("%s[%d]: Ut Setting Times: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* Gate/Curves */
    m_funMap.insert(MainMenu::GateCurves_Gate,          &SubMenu::create_gate_menu);
    m_funMap.insert(MainMenu::GateCurves_Alarm,         &SubMenu::create_alarm_menu);
    m_funMap.insert(MainMenu::GateCurves_Output,        &SubMenu::create_output_menu);
    m_funMap.insert(MainMenu::GateCurves_DAC,           &SubMenu::create_dac_menu);
    m_funMap.insert(MainMenu::GateCurves_TCG,           &SubMenu::create_tcg_menu);
    qDebug("%s[%d]: Gate/Curves: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* Display */
    m_funMap.insert(MainMenu::Display_Selection,        &SubMenu::create_selection_menu);
    m_funMap.insert(MainMenu::Display_ColorSettings,    &SubMenu::create_color_menu);
    m_funMap.insert(MainMenu::Displsy_Properties,       &SubMenu::create_properties_menu);
    qDebug("%s[%d]: Display: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* Probe/Part */
    m_funMap.insert(MainMenu::ProbePart_Select,         &SubMenu::create_probe_selection_menu);
    m_funMap.insert(MainMenu::ProbePart_Position,       &SubMenu::create_position_menu);
    m_funMap.insert(MainMenu::ProbePart_FFT,            &SubMenu::create_fft_menu);
    m_funMap.insert(MainMenu::ProbePart_Part,           &SubMenu::create_part_menu);
    m_funMap.insert(MainMenu::ProbePart_Advanced,       &SubMenu::create_part_advanced_menu);
    qDebug("%s[%d]: Probe/Part: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* Focal Law */
    m_funMap.insert(MainMenu::FocalLaw_LawConfig,       &SubMenu::create_law_config_menu);
    m_funMap.insert(MainMenu::FocalLaw_Angle,           &SubMenu::create_angle_menu);
    m_funMap.insert(MainMenu::FocalLaw_Apeture,         &SubMenu::create_apeture_menu);
    m_funMap.insert(MainMenu::FacalLaw_FocalPoint,      &SubMenu::create_focal_point_menu);
    qDebug("%s[%d]: Focal Law: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* Scan */
    m_funMap.insert(MainMenu::Scan_Inspection,          &SubMenu::create_inspection_menu);
    m_funMap.insert(MainMenu::Scan_Encoder,             &SubMenu::create_encoder_menu);
    m_funMap.insert(MainMenu::Scan_Area,                &SubMenu::create_area_menu);
    m_funMap.insert(MainMenu::Scan_Start,               &SubMenu::create_start_menu);
    qDebug("%s[%d]: Scan: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* Measurement */
    m_funMap.insert(MainMenu::Measurement_Cursors,      &SubMenu::create_cursors_menu);
    m_funMap.insert(MainMenu::Measurement_TOFD,         &SubMenu::create_tofd_menu);
    m_funMap.insert(MainMenu::Measurement_FlawRecord,   &SubMenu::create_flaw_record_menu);
    qDebug("%s[%d]: Measurement: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* File/Report */
    m_funMap.insert(MainMenu::FileReport_File,          &SubMenu::create_file_menu);
    m_funMap.insert(MainMenu::FileReport_SaveMode,      &SubMenu::create_save_mode_menu);
    m_funMap.insert(MainMenu::FileReport_Report,        &SubMenu::create_report_menu);
    m_funMap.insert(MainMenu::FileReport_Format,        &SubMenu::create_format_menu);
    m_funMap.insert(MainMenu::FileReport_UserField,     &SubMenu::create_user_field_menu);
    qDebug("%s[%d]: File/Report: %d(ms)",__func__, __LINE__, time.elapsed());
    time.restart();

    /* Preference */
    m_funMap.insert(MainMenu::Preference_Preference,    &SubMenu::create_preference_menu);
    m_funMap.insert(MainMenu::Preference_System,        &SubMenu::create_system_menu);
    m_funMap.insert(MainMenu::Preference_Network,       &SubMenu::create_network_menu);
    qDebug("%s[%d]: Preference: %d(ms)",__func__, __LINE__, time.elapsed());
}

BaseMenu *SubMenu::create_menu(MainMenu::Type type)
{
    SubMenu::Function pFun = m_funMap.value(type);
    if (pFun == NULL) {
        return NULL;
    }
    BaseMenu *menu = (this->*pFun)();
    menu->setObjectName(QString::number(type));
    layout()->addWidget(menu);
    return menu;
}

BaseMenu *SubMenu::create_general_menu()
{
    return new DplUtSettingMenu::GeneralMenu(this);
}

BaseMenu *SubMenu::create_pulser_menu()
{
    return new DplUtSettingMenu::PulserMenu(this);
}

BaseMenu *SubMenu::create_receiver_menu()
{
    return new DplUtSettingMenu::ReceiverMenu(this);
}

BaseMenu *SubMenu::create_utadvanced_menu()
{
    return new DplUtSettingMenu::UtAdvancedMenu(this);
}

BaseMenu *SubMenu::create_gate_menu()
{
    return new DplGateCurvesMenu::GateMenu(this);
}

BaseMenu *SubMenu::create_alarm_menu()
{
    return new DplGateCurvesMenu::AlarmMenu(this);
}

BaseMenu *SubMenu::create_output_menu()
{
    return new DplGateCurvesMenu::OutputMenu(this);
}

BaseMenu *SubMenu::create_dac_menu()
{
    return new DplGateCurvesMenu::DacMenu(this);
}

BaseMenu *SubMenu::create_tcg_menu()
{
    return new DplGateCurvesMenu::TcgMenu(this);
}

BaseMenu *SubMenu::create_selection_menu()
{
    return new DplDisplayMenu::SelectionMenu(this);
}

BaseMenu *SubMenu::create_color_menu()
{
    return new DplDisplayMenu::ColorSettingMenu(this);
}

BaseMenu *SubMenu::create_properties_menu()
{
    return new DplDisplayMenu::PropertiesMenu(this);
}

BaseMenu *SubMenu::create_probe_selection_menu()
{
    return new DplProbeMenu::SelectionMenu(this);
}

BaseMenu *SubMenu::create_position_menu()
{
    return new DplProbeMenu::PositionMenu(this);
}

BaseMenu *SubMenu::create_fft_menu()
{
    return new DplProbeMenu::FftMenu(this);
}

BaseMenu *SubMenu::create_part_menu()
{
    return new DplProbeMenu::PartMenu(this);
}

BaseMenu *SubMenu::create_part_advanced_menu()
{
    return new DplProbeMenu::AdvancedMenu(this);
}

BaseMenu *SubMenu::create_law_config_menu()
{
    return new DplFocalLawMenu::LawConfigMenu(this);
}

BaseMenu *SubMenu::create_angle_menu()
{
    return new DplFocalLawMenu::AngleMenu(this);
}

BaseMenu *SubMenu::create_apeture_menu()
{
    return new DplFocalLawMenu::ApetureMenu(this);
}

BaseMenu *SubMenu::create_focal_point_menu()
{
    return new DplFocalLawMenu::FocalPointMenu(this);
}

BaseMenu *SubMenu::create_inspection_menu()
{
    return new DplScanMenu::InspectionMenu(this);
}

BaseMenu *SubMenu::create_encoder_menu()
{
    return new DplScanMenu::EncoderMenu(this);
}

BaseMenu *SubMenu::create_area_menu()
{
    return new DplScanMenu::AreaMenu(this);
}

BaseMenu *SubMenu::create_start_menu()
{
    return new DplScanMenu::StartMenu(this);
}

BaseMenu *SubMenu::create_cursors_menu()
{
    return new DplMeasurementMenu::CursorsMenu(this);
}

BaseMenu *SubMenu::create_tofd_menu()
{
    return new DplMeasurementMenu::TofdMenu(this);
}

BaseMenu *SubMenu::create_flaw_record_menu()
{
    return new DplMeasurementMenu::FlawRecordMenu(this);
}

BaseMenu *SubMenu::create_file_menu()
{
    return new DplFileReportMenu::FileMenu(this);
}

BaseMenu *SubMenu::create_save_mode_menu()
{
    return new DplFileReportMenu::SaveModeMenu(this);
}

BaseMenu *SubMenu::create_report_menu()
{
    return new DplFileReportMenu::ReportMenu(this);
}

BaseMenu *SubMenu::create_format_menu()
{
    return new DplFileReportMenu::FormatMenu(this);
}

BaseMenu *SubMenu::create_user_field_menu()
{
    return new DplFileReportMenu::UserFieldMenu(this);
}

BaseMenu *SubMenu::create_preference_menu()
{
    return new DplPreferenceMenu::PreferenceMenu(this);
}

BaseMenu *SubMenu::create_system_menu()
{
    return new DplPreferenceMenu::SystemMenu(this);
}

BaseMenu *SubMenu::create_network_menu()
{
    return new DplPreferenceMenu::NetworkMenu(this);
}

void SubMenu::set_menu(MainMenu::Type type)
{
    if (m_curMenu) {
        m_curMenu->hide();
    }

    m_curMenu = get_menu(type);
    if(m_curMenu) {
        m_curMenu->show();
        return;
    }

    m_curMenu = create_menu(type);
    if (m_curMenu) {
        m_curMenu->show();
    }
}

SubMenu::~SubMenu()
{
}

void SubMenu::set_opacity_main_menu(double value)
{
    qreal alpha = value / 100;
    m_opacityEffect->setOpacity(alpha);
    this->setGraphicsEffect(m_opacityEffect);
}
