#ifndef __UT_REF_MENU_ITEM_H__
#define __UT_REF_MENU_ITEM_H__

#include "ut_menu_item.h"

class UtRefMenuItem : public UtMenuItem
{
    Q_OBJECT
public:
    UtRefMenuItem(QWidget *parent);

protected slots:
    void update_value();
    void do_value_changed(double val);

protected:
    void cursor_change_event(const DplMeasure::CursorPointer &cursor);

private:
    DplMeasure::CursorPointer m_cursor;
};

#endif // __UT_REF_MENU_ITEM_H__
