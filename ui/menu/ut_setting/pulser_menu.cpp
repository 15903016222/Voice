/**
 * @file pulser_menu.cpp
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "pulser_menu.h"

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Combo,
    MenuItem::Label
};

PulserMenu::PulserMenu(Ui::BaseMenu *ui, QObject *parent)
    :BaseMenu(ui, s_types, parent)
{
    QStringList txRxModesList;
    QStringList voltagesList;
    QStringList prfsList;

    txRxModesList.append(tr("PC"));
    txRxModesList.append(tr("PE"));
    txRxModesList.append(tr("TT"));
    txRxModesList.append(tr("TOFD"));

    voltagesList.append("50V");
    voltagesList.append("100V");
    voltagesList.append("200V");

    prfsList.append(tr("Auto Max"));
    prfsList.append(tr("Max/2"));
    prfsList.append(tr("Optimum"));
    prfsList.append(tr("UserDef"));

    m_menuItem[0]->set(tr("Tx/Rx Mode"), txRxModesList);
    m_menuItem[1]->set(tr("Pulser"), "", 1, 113, 0);
    m_menuItem[2]->set(tr("Voltage"), voltagesList);
    m_menuItem[3]->set(tr("PW"), "ns", 30, 1000, 1);
    m_menuItem[4]->set(tr("PRF"), prfsList);
}
