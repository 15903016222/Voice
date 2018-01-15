#include "cursor_menu_item.h"

#include <device/device.h>

CursorMenuItem::CursorMenuItem(QWidget *parent, const QString &title) :
    SpinMenuItem(parent, title)
{
    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update_group()));
}

void CursorMenuItem::disconnect_group(const DplDevice::GroupPointer &group)
{
    disconnect_cursor(group->cursor());
}

void CursorMenuItem::connect_group(const DplDevice::GroupPointer &group)
{
    connect_cursor(group->cursor());
}

void CursorMenuItem::update_group()
{
    if (m_group) {
        disconnect_group(m_group);
    }

    m_group = DplDevice::Device::instance()->current_group();

    connect_group(m_group);
}
