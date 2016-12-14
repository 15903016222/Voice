#ifndef __SUB_MENU_H__
#define __SUB_MENU_H__

#include "main_menu.h"
#include "menu_item.h"
#include "mcu.h"

#include "base_menu.h"

#include <QTreeWidgetItem>
#include <QMap>

#include <QTimer>

namespace Ui {
class SubMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

public slots:
    void set_menu(MainMenu::Type type);

private slots:
    void show_probe_dialog();
    void show_wedge_dialog();
    void show_input_dialog();
    void show_filemanager_dialog();
    void show_ip_address_dialog();
    void show_subnet_mask_dialog();
    void show_info_dialog();
    void show_about_dialog();
    void show_date_dialog();
    void show_time_dialog();
    void show_resetconfig_dialog();
    void set_brightness(double value);
    void auto_detect_probe(QString string);
    void do_probe_event(const Probe &probe);

private:
    Ui::SubMenu *ui;

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
    void init_option_stringlist();
    void init_step_list();

    QList<int> get_dialog_value_list(QString string, QString symbol);

    Mcu *pMcu;

    QList<double> stepList1;
    QList<double> stepList2;
    QList<double> stepList3;
    QList<double> stepList4;
    QList<double> stepList5;
    QList<double> stepList6;

    QStringList switchList;
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

    QMap<MainMenu::Type, BaseMenu*> m_map;

    double m_brightness;  

    MainMenu::Type m_preType;
    MainMenu::Type m_curType;
    QTimer *m_timer;

private slots:
    void do_timeout();
};

#endif // SUB_MENU_H
