/**
 * @file gate_menu.cpp
 * @brief gate menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "gate_menu.h"

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Combo,
    MenuItem::Combo
};

GateMenu::GateMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, s_types, parent)
{
    QStringList gatesList;
    QStringList synchrosList;
    QStringList measureModesList;

    gatesList.append(tr("A"));
    gatesList.append(tr("B"));
    gatesList.append(tr("I"));
    gatesList.append(tr("Off"));

    synchrosList.append(tr("Gate A"));
    synchrosList.append(tr("Gate I"));
    synchrosList.append(tr("Pulse"));

    measureModesList.append(tr("Edge"));
    measureModesList.append(tr("Peak"));

    m_menuItem[0]->set(tr("Gate"), gatesList);
    m_menuItem[1]->set(tr("Start"), "mm", 0, 16000, 2);
    m_menuItem[2]->set(tr("Width"), "mm", 0.05, 525, 2);
    m_menuItem[3]->set(tr("Threshold"), "%", 0, 100, 0);
    m_menuItem[4]->set(tr("Synchro"), synchrosList);
    m_menuItem[5]->set(tr("Measure Mode"), measureModesList);
}
