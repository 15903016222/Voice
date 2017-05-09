/**
 * @file sub_menu.h
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __SUB_MENU_H__
#define __SUB_MENU_H__

#include "main_menu.h"
#include "base_menu.h"

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

//#include <QMap>

namespace Ui {
class BaseMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

    BaseMenu *get_menu(MainMenu::Type type) { return m_map.value(type); }

public slots:
    void set_menu(MainMenu::Type type);
    void set_opacity_main_menu(double value);

private:
    Ui::BaseMenu *ui;

    /* Ut Setting Menu*/
    DplUtSettingMenu::GeneralMenu m_generalMenu;
    DplUtSettingMenu::PulserMenu m_pulserMenu;
    DplUtSettingMenu::ReceiverMenu m_receiverMenu;
    DplUtSettingMenu::UtAdvancedMenu m_utAdvanceMenu;

    /* Gate/curves Menu */
    DplGateCurvesMenu::GateMenu m_gateMenu;
    DplGateCurvesMenu::AlarmMenu m_alarmMenu;
    DplGateCurvesMenu::OutputMenu m_outputMenu;
    DplGateCurvesMenu::DacMenu m_dacMenu;
    DplGateCurvesMenu::TcgMenu m_tcgMenu;

    /* Display Menu */
    DplDisplayMenu::SelectionMenu m_selectionMenu;
    DplDisplayMenu::ColorSettingMenu m_colorSettingMenu;
    DplDisplayMenu::PropertiesMenu m_propertiesMenu;

    /* Probe/Part Menu */
    DplProbeMenu::SelectionMenu m_probeSelectionMenu;
    DplProbeMenu::PositionMenu m_positionMenu;
    DplProbeMenu::FftMenu   m_fftMenu;
    DplProbeMenu::PartMenu  m_partMenu;
    DplProbeMenu::AdvancedMenu m_advanceMenu;

    /* Focal Law Menu */
    DplFocalLawMenu::LawConfigMenu m_lawConfigMenu;
    DplFocalLawMenu::AngleMenu m_angleMenu;
    DplFocalLawMenu::ApetureMenu m_apetureMenu;
    DplFocalLawMenu::FocalPointMenu m_focalPointMenu;

    /* Scan Menu */
    DplScanMenu::InspectionMenu m_inspectionMenu;
    DplScanMenu::EncoderMenu m_encoderMenu;
    DplScanMenu::AreaMenu m_areaMenu;
    DplScanMenu::StartMenu m_startmenu;

    /* Measurement Menu */
    DplMeasurementMenu::CursorsMenu m_cursorsMenu;
    DplMeasurementMenu::TofdMenu m_tofdMenu;
    DplMeasurementMenu::FlawRecordMenu m_flawRecordMenu;

    /* File/Report Menu */
    DplFileReportMenu::FileMenu m_fileMenu;
    DplFileReportMenu::SaveModeMenu m_saveModeMenu;
    DplFileReportMenu::ReportMenu m_reportMenu;
    DplFileReportMenu::FormatMenu m_formatmenu;
    DplFileReportMenu::UserFieldMenu m_userFieldMenu;

    /* Preference */
    DplPreferenceMenu::PreferenceMenu m_preferenceMenu;
    DplPreferenceMenu::SystemMenu m_systemMenu;
    DplPreferenceMenu::NetworkMenu m_networkMenu;

    void init_map();

    QMap<MainMenu::Type, BaseMenu*> m_map;

    MainMenu::Type m_preType;

    QGraphicsOpacityEffect *m_opacityEffect;

};

#endif // SUB_MENU_H
