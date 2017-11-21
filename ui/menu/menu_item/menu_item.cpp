/**
 * @file menu_item.cpp
 * @brief menu item base class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "menu_item.h"

#include <ui/menu/base_menu.h>

MenuItem::MenuItem(QWidget *parent) :
    QWidget(parent),
    m_isEditing(false),
    m_selected(false),
    m_parent(parent)
{}

void MenuItem::set_parent_focus_in(QObject *object)
{
    BaseMenu *parentItem = static_cast<BaseMenu*> (m_parent);
    if(parentItem) {
        parentItem->set_focus(object);
    }
}
