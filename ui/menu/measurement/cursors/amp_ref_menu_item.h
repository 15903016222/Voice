/**
 * @file amp_ref_menu_item.h
 * @brief 幅值参考菜单
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2018-01-11
 */
#ifndef __AMP_REF_MENU_ITEM_H__
#define __AMP_REF_MENU_ITEM_H__

#include "cursor_menu_item.h"

class AmpRefMenuItem : public CursorMenuItem
{
    Q_OBJECT
public:
    AmpRefMenuItem(QWidget *parent);

protected:
    void disconnect_cursor(const DplMeasure::CursorPointer &cursor);
    void connect_cursor(const DplMeasure::CursorPointer &cursor);
};

#endif // __AMP_REF_MENU_ITEM_H__
