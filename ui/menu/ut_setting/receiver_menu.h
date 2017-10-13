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
#include <device/device.h>

namespace DplUtSettingMenu {

class ReceiverMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ReceiverMenu(QWidget *parent = 0);

protected slots:
    void do_receiverItem_changed(double val);
    void do_filterItem_changed(int index);
    void do_rectifierItem_changed(int index);
    void do_videoFilterItem_changed(int index);
    void do_averagingItem_changed(int index);

    void update(const DplDevice::GroupPointer &grp);
    void update_filter_item();
    void update_receiver_item();

private:
    SpinMenuItem *m_receiverItem;
    ComboMenuItem *m_filterItem;
    ComboMenuItem *m_rectifierItem;
    ComboMenuItem *m_videoFilterItem;
    ComboMenuItem *m_averagingItem;

    DplDevice::GroupPointer m_group;
};

}
#endif // __RECEIVER_MENU_H__
