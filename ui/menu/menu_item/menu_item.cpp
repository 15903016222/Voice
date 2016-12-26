/**
 * @file menu_item.cpp
 * @brief menu item base class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "menu_item.h"

MenuItem::MenuItem(QWidget *parent, MenuItem::Type type) : QWidget(parent)
{
    m_type = type;
}

void MenuItem::set(const QString &title, const QString &text)
{
    Q_UNUSED(title);
    Q_UNUSED(text);
}

void MenuItem::set(const QString &title, const QString &unit, double min, double max, int decimals)
{
    Q_UNUSED(title);
    Q_UNUSED(unit);
    Q_UNUSED(min);
    Q_UNUSED(max);
    Q_UNUSED(decimals);
}
