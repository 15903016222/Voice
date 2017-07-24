/**
 * @file receiver_menu.h
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __RECEIVER_MENU_H__
#define __RECEIVER_MENU_H__

#include "../base_menu.h"

namespace DplUtSettingMenu {

class ReceiverMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ReceiverMenu(QWidget *parent = 0);
    ~ReceiverMenu();

private:
    LabelMenuItem *m_receiverItem;
    ComboMenuItem *m_filterItem;
    ComboMenuItem *m_rectifierItem;
    ComboMenuItem *m_videoFilterItem;
    ComboMenuItem *m_averagingItem;
};

}
#endif // __RECEIVER_MENU_H__
