#ifndef __INDEX_MENU_ITEM_H__
#define __INDEX_MENU_ITEM_H__

#include "cursor_menu_item.h"

class IndexMenuItem : public CursorMenuItem
{
    Q_OBJECT
public:
    IndexMenuItem(QWidget *parent, const QString &title);

protected:
//    void disconnect_group(const DplDevice::GroupPointer &group);
//    void connect_group(const DplDevice::GroupPointer &group);

protected slots:
    void update_unit();
    void update_range();
};

#endif // __INDEX_MENU_ITEM_H__
