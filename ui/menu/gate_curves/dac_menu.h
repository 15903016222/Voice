/**
 * @file dac_menu.h
 * @brief dac menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
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
    bool m_settingFlag;

    MenuItem *m_pointItem;
    MenuItem *m_positionItem;
    MenuItem *m_addPointItem;
    MenuItem *m_deletePointItem;

    void show_edit();
    void hide_edit();

private slots:
    void do_mode_event(int pos);
};

#endif // DACMENU_H
