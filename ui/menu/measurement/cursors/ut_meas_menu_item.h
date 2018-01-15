#ifndef __UT_MEAS_MENU_ITEM_H__
#define __UT_MEAS_MENU_ITEM_H__

#include "ut_menu_item.h"

class UtMeasMenuItem : public UtMenuItem
{
    Q_OBJECT
public:
    UtMeasMenuItem(QWidget *parent);

protected slots:
    void update_value();
    void do_value_changed(double val);

protected:
    void disconnect_cursor(const DplMeasure::CursorPointer &cursor);
    void connect_cursor(const DplMeasure::CursorPointer &cursor);
};

#endif // __UT_MEAS_MENU_ITEM_H__
