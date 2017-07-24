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

class SubMenu : public QWidget
{
    Q_OBJECT
public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

    BaseMenu *get_menu(MainMenu::Type type);

public slots:
    void set_menu(MainMenu::Type type);
    void set_opacity_main_menu(double value);

    void init_map();

private:
    BaseMenu *m_curMenu;

    typedef BaseMenu *(SubMenu::*Function)();
    QMap<MainMenu::Type, SubMenu::Function> m_funMap;

    QGraphicsOpacityEffect *m_opacityEffect;

    BaseMenu *create_menu(MainMenu::Type type);
    /* UT Setting */
    BaseMenu *create_general_menu();
    BaseMenu *create_pulser_menu();
    BaseMenu *create_receiver_menu();
    BaseMenu *create_utadvanced_menu();
    /* Gate/Curves */
    BaseMenu *create_gate_menu();
    BaseMenu *create_alarm_menu();
    BaseMenu *create_output_menu();
    BaseMenu *create_dac_menu();
    BaseMenu *create_tcg_menu();
    /* Display */
    BaseMenu *create_selection_menu();
    BaseMenu *create_color_menu();
    BaseMenu *create_properties_menu();
    /* Probe/Part */
    BaseMenu *create_probe_selection_menu();
    BaseMenu *create_position_menu();
    BaseMenu *create_fft_menu();
    BaseMenu *create_part_menu();
    BaseMenu *create_part_advanced_menu();
    /* Focal law */
    BaseMenu *create_law_config_menu();
    BaseMenu *create_angle_menu();
    BaseMenu *create_apeture_menu();
    BaseMenu *create_focal_point_menu();
    /* Scan */
    BaseMenu *create_inspection_menu();
    BaseMenu *create_encoder_menu();
    BaseMenu *create_area_menu();
    BaseMenu *create_start_menu();
    /* Measurement */
    BaseMenu *create_cursors_menu();
    BaseMenu *create_tofd_menu();
    BaseMenu *create_flaw_record_menu();
    /* File/Report */
    BaseMenu *create_file_menu();
    BaseMenu *create_save_mode_menu();
    BaseMenu *create_report_menu();
    BaseMenu *create_format_menu();
    BaseMenu *create_user_field_menu();
    /* Preference */
    BaseMenu *create_preference_menu();
    BaseMenu *create_system_menu();
    BaseMenu *create_network_menu();
};

inline BaseMenu *SubMenu::get_menu(MainMenu::Type type)
{
    return this->findChild<BaseMenu *>(QString::number(type));
}

#endif // SUB_MENU_H
