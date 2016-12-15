#ifndef __DAC_MENU_H__
#define __DAC_MENU_H__

#include "base_menu.h"

class DacMenu : public BaseMenu
{
    Q_OBJECT
public:
    DacMenu(Ui::SubMenu *ui, QObject *parent);

    void show();
    void hide();

private:
    QStringList m_modes;
    QStringList m_curveXs;
    QStringList m_points;

    bool m_settingFlag;

    void mode_item();

    void show_setting();
    void show_edit();

    /* Setting */
    void curve_no_item();
    void curve_x_item();
    void db_offset_item();
    void ref_gain_item();
    void switch_item();

    /* Edit */
    void point_item();
    void position_item();
    void add_point_item();
    void delete_point_item();

private slots:
    void do_mode_event(int pos);
};

#endif // DACMENU_H
