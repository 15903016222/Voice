#ifndef __SCAN_MENU_ITEM_H__
#define __SCAN_MENU_ITEM_H__

#include "cursor_menu_item.h"

class ScanMenuItem : public CursorMenuItem
{
    Q_OBJECT
public:
    ScanMenuItem(QWidget *parent, const QString &title);

protected:
//    void disconnect_group(const DplDevice::GroupPointer &group);
    void connect_group(const DplDevice::GroupPointer &group);

protected slots:
    void update_unit();
    void update_range();
};

#endif // __SCAN_MENU_ITEM_H__
