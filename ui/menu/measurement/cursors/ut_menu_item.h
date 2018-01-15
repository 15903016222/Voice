#ifndef __UT_MENU_ITEM_H__
#define __UT_MENU_ITEM_H__

#include "cursor_menu_item.h"

class UtMenuItem : public CursorMenuItem
{
    Q_OBJECT
public:
    UtMenuItem(QWidget *parent, const QString &title);

protected slots:
    void update_unit(DplDevice::Group::UtUnit type);
    void update_range();
    virtual void update_value() = 0;

protected:
    void disconnect_group(const DplDevice::GroupPointer &group);
    void connect_group(const DplDevice::GroupPointer &group);
};

#endif // __UT_MENU_ITEM_H__
