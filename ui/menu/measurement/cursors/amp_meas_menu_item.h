/**
 * @file amp_meas_menu_item.h
 * @brief 幅值测量菜单
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2018-01-11
 */
#ifndef __AMP_MEAS_MENU_ITEM_H__
#define __AMP_MEAS_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class AmpMeasMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    AmpMeasMenuItem(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);

private:
    DplMeasure::CursorPointer m_cursor;
};

#endif // __AMP_MEAS_MENU_ITEM_H__
