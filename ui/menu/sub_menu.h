#ifndef SUB_MENU_H
#define SUB_MENU_H

#include "menu_item.h"
#include "menu_config.h"
#include "networkdialog.h"
#include "datetimesetdialog.h"

#include <QWidget>
#include <QTreeWidgetItem>
#include <QMap>

namespace Ui {
class SubMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    enum Type {
        UTSettings_General      = 1,
        UTSettings_Pulser,
        UTSettings_Receiver,
        UTSettings_Advanced,
        GateCurves_Gate,
        GateCurves_Alarm,
        GateCurves_Output,
        GateCurves_DAC,
        GateCurves_TCG,
        Display_Selection,
        Display_ColorSettings,
        Displsy_Properties,
        ProbePart_Select,
        ProbePart_Position,
        ProbePart_FFT,
        ProbePart_Part,
        ProbePart_Advanced,
        FocalLaw_LawConfig,
        FocalLaw_Angle,
        FocalLaw_Apeture,
        FacalLaw_FocalPoint,
        Scan_Inspection,
        Scan_Encoder,
        Scan_Area,
        Scan_Start,
        Measurement_Cursors,
        Measurement_TOFD,
        Measurement_FlawRecord,
        FileReport_File,
        FileReport_SaveMode,
        FileReport_Report,
        FileReport_Format,
        FileReport_UserField,
        Preference_Preference,
        Preference_System,
        Preference_Network,
        Preference_Service
    };

    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

    typedef void (SubMenu::*Function)(bool);

private:
    Ui::SubMenu *ui;

    void set_general_menu(bool show);
    void set_pulser_menu(bool show);
    void set_receiver_menu(bool show);
    void set_advanced_menu(bool show);

    void set_gate_menu(bool show);
    void set_alarm_menu(bool show);
    void set_output_menu(bool show);
    void set_dac_menu(bool show);
    void set_tcg_menu(bool show);

    void set_selection_menu(bool show);
    void set_colorSettings_menu(bool show);
    void set_properties_menu(bool show);

    void set_select_menu(bool show);
    void set_position_menu(bool show);
    void set_fft_menu(bool show);
    void set_part_menu(bool show);
    void set_advanced_2_menu(bool show);

    void set_lawConfig_menu(bool show);
    void set_angle_menu(bool show);
    void set_apeture_menu(bool show);
    void set_focalPoint_menu(bool show);

    void set_inspection_menu(bool show);
    void set_encoder_menu(bool show);
    void set_area_menu(bool show);
    void set_start_menu(bool show);

    void set_cursors_menu(bool show);
    void set_tofd_menu(bool show);
    void set_flawRecord_menu(bool show);

    void set_file_menu(bool show);
    void set_saveMode_menu(bool show);
    void set_report_menu(bool show);
    void set_format_menu(bool show);
    void set_userField_menu(bool show);

    void set_preference_menu(bool show);
    void set_system_menu(bool show);
    void set_network_menu(bool show);
    void set_service_menu(bool show);

    void set_spinbox_menu(MenuItem *widget, const QString &title, const QString &unit, QList<double> &steps, double min, double max, int decimals);
    void set_combobox_menu(MenuItem *widget, const QString &title, QStringList &texts);
    void set_label_menu(MenuItem *widget, const QString &title);
    void init_map();
    void run_fun(Type type, bool value);
    void get_main_menu_type(Type type);
    void init_option_stringlist();
    void init_step_list();

    MenuConfig *menuConfig;
    NetworkDialog *pNetworkDialog;
    DateTimeSetDialog *pDateTimeSetDialog;

    QList<double> stepList1;
    QList<double> stepList2;
    QList<double> stepList3;
    QList<double> stepList4;
    QList<double> stepList5;
    QList<double> stepList6;


    QStringList switchList;
    QStringList m_list_utUnit;
    QStringList m_list_txrxMode;
    QStringList m_list_voltage;
    QStringList m_list_prf;
    QStringList m_list_filter;
    QStringList m_list_rectifier;
    QStringList m_list_averaging;
    QStringList m_list_pointQty;
    QStringList m_list_gate;
    QStringList m_list_synchro;
    QStringList m_list_measureMode;
    QStringList m_list_alarm;
    QStringList m_list_group;
    QStringList m_list_condition;
    QStringList m_list_operator;
    QStringList m_list_output;
    QStringList m_list_sound;
    QStringList m_list_data;
    QStringList m_list_mode;
    QStringList m_list_curveX;
    QStringList m_list_point;
    QStringList m_list_group2;
    QStringList m_list_display;
    QStringList m_list_cScanSource;
    QStringList m_list_scan;
    QStringList m_list_color;
    QStringList m_list_envelope;
    QStringList m_list_cScanMode;
    QStringList m_list_group3;
    QStringList m_list_groupMode;
    QStringList m_list_define;
    QStringList m_list_skew;
    QStringList m_list_geometry;
    QStringList m_list_material;
    QStringList m_list_lawType;
    QStringList m_list_waveType;
    QStringList m_list_type;
    QStringList m_list_scan2;
    QStringList m_list_type2;
    QStringList m_list_encoder;
    QStringList m_list_encoderType;
    QStringList m_list_polarity;
    QStringList m_list_selection;
    QStringList m_list_select;
    QStringList m_list_storage;
    QStringList m_list_saveMode;
    QStringList m_list_select2;
    QStringList m_list_units;
    QStringList m_list_language;
    QStringList m_list_certImport;

    QMap<QString, Type> m_typeMap;
    QMap<Type, Function> m_map;

private slots:
    void set_third_menu(int num);
    void show_probe_dialog();
    void show_wedge_dialog();
    void show_input_dialog();
    void show_filemanager_dialog();
    void show_network_dialog();
    void show_info_dialog();
    void show_about_dialog();
    void show_datetime_dialog();
    void show_resetconfig_dialog();



};

#endif // SUB_MENU_H
