#ifndef __CURSOR_MENU_ITEM_H__
#define __CURSOR_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"
#include <device/group.h>

class CursorMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    CursorMenuItem(QWidget *parent, const QString &title);

protected:
    virtual void disconnect_group(const DplDevice::GroupPointer &group);
    virtual void connect_group(const DplDevice::GroupPointer &group);
    virtual void disconnect_cursor(const DplMeasure::CursorPointer &cursor) = 0;
    virtual void connect_cursor(const DplMeasure::CursorPointer &cursor) = 0;

protected slots:
    void update_group();

private:
    DplDevice::GroupPointer m_group;
};

#endif // __CURSOR_MENU_ITEM_H__
