#ifndef __SCAN_REF_MENU_ITEM_H__
#define __SCAN_REF_MENU_ITEM_H__

#include "scan_menu_item.h"

class ScanRefMenuItem : public ScanMenuItem
{
public:
    ScanRefMenuItem(QWidget *parent);

protected:
    void disconnect_cursor(const DplMeasure::CursorPointer &cursor);
    void connect_cursor(const DplMeasure::CursorPointer &cursor);
};

#endif // __SCAN_REF_MENU_ITEM_H__
