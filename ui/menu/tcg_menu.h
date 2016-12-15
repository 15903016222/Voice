#ifndef __TCG_MENU_H__
#define __TCG_MENU_H__

#include "base_menu.h"

class TcgMenu : public BaseMenu
{
    Q_OBJECT
public:
    TcgMenu(Ui::SubMenu *ui, QObject *parent);

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

    void curve_no_item();
    void curve_x_item();
    void db_offset_item();
    void switch_item();

    void point_item();
    void position_item();
    void gain_item();
    void add_point_item();
    void delete_point_item();

private slots:
    void do_mode_event(int pos);
};

#endif // __TCG_MENU_H__
