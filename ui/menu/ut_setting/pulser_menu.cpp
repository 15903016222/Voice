/**
 * @file pulser_menu.cpp
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "pulser_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"

namespace DplUtSettingMenu {

PulserMenu::PulserMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
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

    m_txrxModeItem.set(tr("Tx/Rx Mode"), txRxModesList);

    m_pulserItem.set(tr("Pulser"), "", 1, 113, 0);

    m_voltageItem.set(tr("Voltage"), voltagesList);

    m_pwItem.set(tr("PW"), "ns", 30, 1000, 1);

    m_prfItem.set(tr("PRF"), prfsList);
}

PulserMenu::~PulserMenu()
{
}

void PulserMenu::show()
{
    ui->menuItem0->layout()->addWidget(&m_txrxModeItem);
    ui->menuItem1->layout()->addWidget(&m_pulserItem);
    ui->menuItem2->layout()->addWidget(&m_voltageItem);
    ui->menuItem3->layout()->addWidget(&m_pwItem);
    ui->menuItem4->layout()->addWidget(&m_prfItem);
    m_txrxModeItem.show();
    m_pulserItem.show();
    m_voltageItem.show();
    m_pwItem.show();
    m_prfItem.show();
}

void PulserMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(&m_txrxModeItem);
    ui->menuItem1->layout()->removeWidget(&m_pulserItem);
    ui->menuItem2->layout()->removeWidget(&m_voltageItem);
    ui->menuItem3->layout()->removeWidget(&m_pwItem);
    ui->menuItem4->layout()->removeWidget(&m_prfItem);
    m_txrxModeItem.hide();
    m_pulserItem.hide();
    m_voltageItem.hide();
    m_pwItem.hide();
    m_prfItem.hide();
}

}
