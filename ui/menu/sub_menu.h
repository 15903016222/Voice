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

    MenuConfig *menuConfig;
    NetworkDialog *pNetworkDialog;
    DateTimeSetDialog *pDateTimeSetDialog;

    QList<double> stepList1;
    QList<double> stepList2;
    QList<double> stepList3;
    QList<double> stepList4;
    QList<double> stepList5;

    QStringList materialList;
    QStringList switchList;

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
