/**
 * @file pulser_menu.cpp
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "pulser_menu.h"
#include <QDebug>

PulserMenu::PulserMenu(Ui::SubMenu *ui, QObject *parent)
    :BaseMenu(ui, parent)
{
    m_txRxMode.append(tr("PC"));
    m_txRxMode.append(tr("PE"));
    m_txRxMode.append(tr("TT"));
    m_txRxMode.append(tr("TOFD"));

    m_voltages.append("50V");
    m_voltages.append("100V");
    m_voltages.append("200V");

    m_prfs.append(tr("Auto Max"));
    m_prfs.append(tr("Max/2"));
    m_prfs.append(tr("Optimum"));
    m_prfs.append(tr("UserDef"));

    m_txrxItem = new ComboMenuItem();
    m_pulserItem = new SpinMenuItem();
    m_voltagesItem = new ComboMenuItem();
    m_pwItem = new SpinMenuItem();
    m_prfItem = new ComboMenuItem();
    m_noneItem = new LabelMenuItem();

    m_txrxItem->set(tr("Tx/Rx Mode"), m_txRxMode);
    m_pulserItem->set(tr("Pulser"), "", 1, 113, 0);
    m_voltagesItem->set(tr("Voltage"), m_voltages);
    m_pwItem->set(tr("PW"), "ns", 30, 500, 1);
    m_prfItem->set(tr("PRF"), m_prfs);
}

PulserMenu::~PulserMenu()
{
    delete m_txrxItem;
    delete m_pulserItem;
    delete m_voltagesItem;
    delete m_pwItem;
    delete m_prfItem;
    delete m_noneItem;
}

void PulserMenu::show()
{
    ui->menuItem1->layout()->addWidget(m_txrxItem);
    ui->menuItem2->layout()->addWidget(m_pulserItem);
    ui->menuItem3->layout()->addWidget(m_voltagesItem);
    ui->menuItem4->layout()->addWidget(m_pwItem);
    ui->menuItem5->layout()->addWidget(m_prfItem);
    ui->menuItem6->layout()->addWidget(m_noneItem);

    m_txrxItem->show();
    m_pulserItem->show();
    m_voltagesItem->show();
    m_pwItem->show();
    m_prfItem->show();
    m_noneItem->show();
}

void PulserMenu::hide()
{
    ui->menuItem1->layout()->removeWidget(m_txrxItem);
    ui->menuItem2->layout()->removeWidget(m_pulserItem);
    ui->menuItem3->layout()->removeWidget(m_voltagesItem);
    ui->menuItem4->layout()->removeWidget(m_pwItem);
    ui->menuItem5->layout()->removeWidget(m_prfItem);
    ui->menuItem6->layout()->removeWidget(m_noneItem);

    m_txrxItem->hide();
    m_pulserItem->hide();
    m_voltagesItem->hide();
    m_pwItem->hide();
    m_prfItem->hide();
    m_noneItem->hide();
}
