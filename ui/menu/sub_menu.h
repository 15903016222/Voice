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
#include "mcu.h"

#include <QTreeWidgetItem>
#include <QMap>

#include "base_menu.h"

namespace Ui {
class BaseMenu;
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
    Ui::BaseMenu *ui;

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
};

#endif // SUB_MENU_H
