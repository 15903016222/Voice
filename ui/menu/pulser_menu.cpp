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

    m_txrxItem = new MenuItem();
    m_pulserItem = new MenuItem();
    m_voltagesItem = new MenuItem();
    m_pwItem = new MenuItem();
    m_prfItem = new MenuItem();
    m_noneItem = new MenuItem();

    m_txrxItem->set_combo(tr("Tx/Rx Mode"), m_txRxMode);
    m_pulserItem->set_spin(tr("Pulser"), "", 1, 113, 0);
    m_voltagesItem->set_combo(tr("Voltage"), m_voltages);
    m_pwItem->set_spin(tr("PW"), "ns", 30, 500, 1);
    m_prfItem->set_combo(tr("PRF"), m_prfs);
    m_noneItem->set_type(MenuItem::None);
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
    qDebug()<<__func__<<__LINE__;
    ui->subMenu_1->layout()->addWidget(m_txrxItem);
    ui->subMenu_2->layout()->addWidget(m_pulserItem);
    ui->subMenu_3->layout()->addWidget(m_voltagesItem);
    ui->subMenu_4->layout()->addWidget(m_pwItem);
    ui->subMenu_5->layout()->addWidget(m_prfItem);
    ui->subMenu_6->layout()->addWidget(m_noneItem);

    m_txrxItem->show();
    m_pulserItem->show();
    m_voltagesItem->show();
    m_pwItem->show();
    m_prfItem->show();
    m_noneItem->show();
    qDebug()<<__func__<<__LINE__;
}

void PulserMenu::hide()
{
    qDebug()<<__func__<<__LINE__;
    ui->subMenu_1->layout()->removeWidget(m_txrxItem);
    ui->subMenu_2->layout()->removeWidget(m_pulserItem);
    ui->subMenu_3->layout()->removeWidget(m_voltagesItem);
    ui->subMenu_4->layout()->removeWidget(m_pwItem);
    ui->subMenu_5->layout()->removeWidget(m_prfItem);
    ui->subMenu_6->layout()->removeWidget(m_noneItem);

    m_txrxItem->hide();
    m_pulserItem->hide();
    m_voltagesItem->hide();
    m_pwItem->hide();
    m_prfItem->hide();
    m_noneItem->hide();

    qDebug()<<__func__<<__LINE__;
}
