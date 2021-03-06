/**
 * @file system_menu.h
 * @brief system menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#ifndef __SYSTEM_MENU_H__
#define __SYSTEM_MENU_H__

#include"base_menu.h"

namespace DplPreferenceMenu {

class SystemMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit SystemMenu(Ui::BaseMenu *ui, QObject *parent);
    ~SystemMenu();

    void show();
    void hide();

private:
    LabelMenuItem *m_dateItem;
    LabelMenuItem *m_timeItem;
    ComboMenuItem *m_certItem;
    MenuItem *m_updateItem;
    MenuItem *m_resetCfgItem;
    MenuItem *m_infoItem;

private slots:
    void show_time_dialog();
    void show_date_dialog();
    void show_resetconfig_dialog();
    void show_info_dialog();
};

}
#endif // __SYSTEM_MENU_H__
