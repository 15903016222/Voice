#ifndef __INDEX_REF_MENU_ITEM_H__
#define __INDEX_REF_MENU_ITEM_H__

#include "index_menu_item.h"

class IndexRefMenuItem : public IndexMenuItem
{
public:
    IndexRefMenuItem(QWidget *parent);

protected:
    void disconnect_cursor(const DplMeasure::CursorPointer &cursor);
    void connect_cursor(const DplMeasure::CursorPointer &cursor);
};

#endif // __INDEX_REF_MENU_ITEM_H__
