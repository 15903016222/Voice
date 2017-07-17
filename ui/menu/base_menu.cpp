/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "base_menu.h"

QStringList BaseMenu::s_onOff;

BaseMenu::BaseMenu(Ui::BaseMenu *ui, QObject *parent) :
    QObject(parent),
    m_isHidden(false),
    m_updated(true)
{
    this->ui = ui;

    if (s_onOff.isEmpty()) {
        s_onOff.append(tr("On"));
        s_onOff.append(tr("Off"));
    }
}

BaseMenu::~BaseMenu()
{
}
