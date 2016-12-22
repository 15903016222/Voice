/**
 * @file receiver_menu.h
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __RECEIVER_MENU_H__
#define __RECEIVER_MENU_H__

#include "base_menu.h"

namespace DplUtSettingMenu {

class ReceiverMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ReceiverMenu(Ui::BaseMenu *ui, QObject *parent = 0);
    ~ReceiverMenu();

    void show();
    void hide();

private:
    MenuItem *m_receiverItem;
    MenuItem *m_filterItem;
    MenuItem *m_rectifierItem;
    MenuItem *m_videoFilterItem;
    MenuItem *m_averaginItem;
};

}
#endif // __RECEIVER_MENU_H__
