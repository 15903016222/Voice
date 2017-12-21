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

#include <QStackedLayout>

SubMenu::SubMenu(QWidget *parent) : QWidget(parent)
{
    create_menus();

    set_menu(MainMenu::UTSettings_General);

    set_opacity_main_menu(80);
}

SubMenu::~SubMenu()
{
}

void SubMenu::set_menu(MainMenu::Type type)
{
    m_layout->setCurrentIndex(type);
}

void SubMenu::set_opacity_main_menu(double value)
{
    QGraphicsOpacityEffect opacityEffect;
    opacityEffect.setOpacity(value / 100);
    this->setGraphicsEffect(&opacityEffect);
}

void SubMenu::create_menus()
{
    QStackedLayout *l = new QStackedLayout(this);
    l->setContentsMargins(0, 0, 0, 0);
    l->setSpacing(0);

    m_layout = l;

    /* UT Setting */
    l->addWidget(new DplUtSettingMenu::GeneralMenu(this));
    l->addWidget(new DplUtSettingMenu::PulserMenu(this));
    l->addWidget(new DplUtSettingMenu::ReceiverMenu(this));
    l->addWidget(new DplUtSettingMenu::UtAdvancedMenu(this));

    /* Gate/Curves */
    l->addWidget(new DplGateCurvesMenu::GateMenu(this));
    l->addWidget(new DplGateCurvesMenu::AlarmMenu(this));
    l->addWidget(new DplGateCurvesMenu::AnalogMenu(this));
    l->addWidget(new DplGateCurvesMenu::DacMenu(this));
    l->addWidget(new DplGateCurvesMenu::TcgMenu(this));

    /* Display */
    l->addWidget(new DplDisplayMenu::SelectionMenu(this));
    l->addWidget(new DplDisplayMenu::ColorSettingMenu(this));
    l->addWidget(new DplDisplayMenu::PropertiesMenu(this));

    /* Probe/Part */
    l->addWidget(new DplProbeMenu::SelectionMenu(this));
    l->addWidget(new DplProbeMenu::PositionMenu(this));
    l->addWidget(new DplProbeMenu::FftMenu(this));
    l->addWidget(new DplProbeMenu::PartMenu(this));
    l->addWidget(new DplProbeMenu::AdvancedMenu(this));

    /* Focal Law */
    l->addWidget(new DplFocalLawMenu::LawConfigMenu(this));
    l->addWidget(new DplFocalLawMenu::AngleMenu(this));
    l->addWidget(new DplFocalLawMenu::ApetureMenu(this));
    l->addWidget(new DplFocalLawMenu::FocalPointMenu(this));

    /* Scan */
    l->addWidget(new DplScanMenu::InspectionMenu(this));
    l->addWidget(new DplScanMenu::EncoderMenu(this));
    l->addWidget(new DplScanMenu::AreaMenu(this));
    l->addWidget(new DplScanMenu::StartMenu(this));

    /* Measurement */
    l->addWidget(new DplMeasurementMenu::CursorsMenu(this));
    l->addWidget(new DplMeasurementMenu::TofdMenu(this));
    l->addWidget(new DplMeasurementMenu::FlawRecordMenu(this));

    /* File/Report */
    l->addWidget(new DplFileReportMenu::FileMenu(this));
    l->addWidget(new DplFileReportMenu::SaveModeMenu(this));
    l->addWidget(new DplFileReportMenu::ReportMenu(this));
    l->addWidget(new DplFileReportMenu::FormatMenu(this));
    l->addWidget(new DplFileReportMenu::UserFieldMenu(this));

    /* Preference */
    l->addWidget(new DplPreferenceMenu::PreferenceMenu(this));
    l->addWidget(new DplPreferenceMenu::SystemMenu(this));
    l->addWidget(new DplPreferenceMenu::NetworkMenu(this));
}
