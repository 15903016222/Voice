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
    ui(new Ui::BaseMenu)
{
    ui->setupUi(this);

    QVBoxLayout *layout1 = new QVBoxLayout(ui->menuItem0);
    QVBoxLayout *layout2 = new QVBoxLayout(ui->menuItem1);
    QVBoxLayout *layout3 = new QVBoxLayout(ui->menuItem2);
    QVBoxLayout *layout4 = new QVBoxLayout(ui->menuItem3);
    QVBoxLayout *layout5 = new QVBoxLayout(ui->menuItem4);
    QVBoxLayout *layout6 = new QVBoxLayout(ui->menuItem5);
    layout1->setContentsMargins(0, 0, 0, 0);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout3->setContentsMargins(0, 0, 0, 0);
    layout4->setContentsMargins(0, 0, 0, 0);
    layout5->setContentsMargins(0, 0, 0, 0);
    layout6->setContentsMargins(0, 0, 0, 0);

    init_map();  

    m_preType = MainMenu::UTSettings_Pulser;
    set_menu(MainMenu::UTSettings_General);
}

void SubMenu::init_map()
{
    /* UT Setting */
    m_map.insert(MainMenu::UTSettings_General, new GeneralMenu(ui, this));
    m_map.insert(MainMenu::UTSettings_Pulser, new PulserMenu(ui, this));
    m_map.insert(MainMenu::UTSettings_Receiver, new ReceiverMenu(ui, this));
    m_map.insert(MainMenu::UTSettings_Advanced, new UtAdvancedMenu(ui, this));

    /* Gate/Curves */
    m_map.insert(MainMenu::GateCurves_Gate, new GateMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_Alarm, new AlarmMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_Output, new OutputMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_DAC, new DacMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_TCG, new TcgMenu(ui, this));

    /* Display */
    m_map.insert(MainMenu::Display_Selection,   new DplDisplayMenu::SelectionMenu(ui, this));
    m_map.insert(MainMenu::Display_ColorSettings,   new DplDisplayMenu::ColorSettingMenu(ui, this));
    m_map.insert(MainMenu::Displsy_Properties,  new DplDisplayMenu::PropertiesMenu(ui, this));

    /* Probe/Part */
    m_map.insert(MainMenu::ProbePart_Select,    new DplProbeMenu::SelectionMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_Position,  new DplProbeMenu::PositionMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_FFT,       new DplProbeMenu::FftMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_Part,      new DplProbeMenu::PartMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_Advanced,  new DplProbeMenu::AdvancedMenu(ui, this));

    /* Focal Law */
    m_map.insert(MainMenu::FocalLaw_LawConfig,  new DplFocalLawMenu::LawConfigMenu(ui, this));
    m_map.insert(MainMenu::FocalLaw_Angle,      new DplFocalLawMenu::AngleMenu(ui, this));
    m_map.insert(MainMenu::FocalLaw_Apeture,    new DplFocalLawMenu::ApetureMenu(ui, this));
    m_map.insert(MainMenu::FacalLaw_FocalPoint, new DplFocalLawMenu::FocalPointMenu(ui, this));

    /* Scan */
    m_map.insert(MainMenu::Scan_Inspection,     new DplScanMenu::InspectionMenu(ui, this));
    m_map.insert(MainMenu::Scan_Encoder,        new DplScanMenu::EncoderMenu(ui, this));
    m_map.insert(MainMenu::Scan_Area,           new DplScanMenu::AreaMenu(ui, this));
    m_map.insert(MainMenu::Scan_Start,          new DplScanMenu::StartMenu(ui, this));

    /* Measurement */
    m_map.insert(MainMenu::Measurement_Cursors, new DplMeasurementMenu::CursorsMenu(ui, this));
    m_map.insert(MainMenu::Measurement_TOFD,    new DplMeasurementMenu::TofdMenu(ui, this));
    m_map.insert(MainMenu::Measurement_FlawRecord,  new DplMeasurementMenu::FlawRecordMenu(ui, this));

    /* File/Report */
    m_map.insert(MainMenu::FileReport_File,     new DplFileReportMenu::FileMenu(ui, this));
    m_map.insert(MainMenu::FileReport_SaveMode, new DplFileReportMenu::SaveModeMenu(ui, this));
    m_map.insert(MainMenu::FileReport_Report,   new DplFileReportMenu::ReportMenu(ui, this));
    m_map.insert(MainMenu::FileReport_Format,   new DplFileReportMenu::FormatMenu(ui, this));
    m_map.insert(MainMenu::FileReport_UserField,new DplFileReportMenu::UserFieldMenu(ui, this));

    /* Preference */
    m_map.insert(MainMenu::Preference_Preference, new DplPreferenceMenu::PreferenceMenu(ui, this));
    m_map.insert(MainMenu::Preference_System,   new DplPreferenceMenu::SystemMenu(ui, this));
    m_map.insert(MainMenu::Preference_Network,  new DplPreferenceMenu::NetworkMenu(ui, this));
}


void SubMenu::set_menu(MainMenu::Type type)
{
    if (type == m_preType) {
        return;
    }

    BaseMenu *menu = m_map.value(m_preType);
    if (menu) {
        menu->hide();
    }

    menu = m_map.value(type);
    if(menu) {
        menu->show();
    }

    m_preType = type;
}

SubMenu::~SubMenu()
{
    delete ui;
}
