/**
 * @file amp_ref_menu_item.h
 * @brief 幅值参考菜单
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2018-01-11
 */
#ifndef __AMP_REF_MENU_ITEM_H__
#define __AMP_REF_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class AmpRefMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    AmpRefMenuItem(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);

private:
    DplMeasure::CursorPointer m_cursor;
};

#endif // __AMP_REF_MENU_ITEM_H__
