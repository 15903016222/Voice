/**
 * @file pulser_menu.h
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#ifndef __PULSER_MENU_H__
#define __PULSER_MENU_H__

#include "base_menu.h"

namespace DplUtSettingMenu {

class PulserMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit PulserMenu(Ui::BaseMenu *ui, QObject *parent);
    ~PulserMenu();

    void show();
    void hide();

private:
    MenuItem *m_txrxModeItem;
    MenuItem *m_pulserItem;
    MenuItem *m_voltageItem;
    MenuItem *m_pwItem;
    MenuItem *m_prfItem;
};

}
#endif // __PULSER_MENU_H__
