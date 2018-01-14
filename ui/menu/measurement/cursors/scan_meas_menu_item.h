#ifndef __SCAN_MEAS_MENU_ITEM_H__
#define __SCAN_MEAS_MENU_ITEM_H__

#include "scan_menu_item.h"

class ScanMeasMenuItem : public ScanMenuItem
{
public:
    ScanMeasMenuItem(QWidget *parent);

protected:
    void disconnect_cursor(const DplMeasure::CursorPointer &cursor);
    void connect_cursor(const DplMeasure::CursorPointer &cursor);
};

#endif // __SCAN_MEAS_MENU_ITEM_H__
