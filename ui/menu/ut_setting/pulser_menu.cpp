/**
 * @file pulser_menu.cpp
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "pulser_menu.h"
#include "ui_base_menu.h"

namespace DplUtSettingMenu {

PulserMenu::PulserMenu(QWidget *parent) :
    BaseMenu(parent),
    m_txrxModeItem(new ComboMenuItem(this, tr("Tx/Rx Mode"))),
    m_pulserItem(new SpinMenuItem(this, tr("Pulser"))),
    m_voltageItem(new ComboMenuItem(this, tr("Voltage"))),
    m_pwItem(new SpinMenuItem(this, tr("PW"), "ns")),
    m_prfItem(new ComboMenuItem(this, tr("PRF")))
{
    ui->layout0->addWidget(m_txrxModeItem);
    ui->layout1->addWidget(m_pulserItem);
    ui->layout2->addWidget(m_voltageItem);
    ui->layout3->addWidget(m_pwItem);
    ui->layout4->addWidget(m_prfItem);

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

    m_txrxModeItem->set(txRxModesList);

    m_pulserItem->set(1, 113, 0);

    m_voltageItem->set(voltagesList);

    m_pwItem->set(30, 1000, 1);

    m_prfItem->set(prfsList);
}

PulserMenu::~PulserMenu()
{
}

}
