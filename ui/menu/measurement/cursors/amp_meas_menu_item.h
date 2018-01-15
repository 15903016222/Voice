/**
 * @file amp_meas_menu_item.h
 * @brief 幅值测量菜单
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2018-01-11
 */
#ifndef __AMP_MEAS_MENU_ITEM_H__
#define __AMP_MEAS_MENU_ITEM_H__

#include "cursor_menu_item.h"

class AmpMeasMenuItem : public CursorMenuItem
{
    Q_OBJECT
public:
    AmpMeasMenuItem(QWidget *parent);

protected slots:
    void disconnect_cursor(const DplMeasure::CursorPointer &cursor);
    void connect_cursor(const DplMeasure::CursorPointer &cursor);
};

#endif // __AMP_MEAS_MENU_ITEM_H__
