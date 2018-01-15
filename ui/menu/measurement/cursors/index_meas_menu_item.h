#ifndef __INDEX_MEAS_MENU_ITEM_H__
#define __INDEX_MEAS_MENU_ITEM_H__

#include "index_menu_item.h"

class IndexMeasMenuItem : public IndexMenuItem
{
public:
    IndexMeasMenuItem(QWidget *parent);

protected:
    void disconnect_cursor(const DplMeasure::CursorPointer &cursor);
    void connect_cursor(const DplMeasure::CursorPointer &cursor);
};

#endif // __INDEX_MEAS_MENU_ITEM_H__
