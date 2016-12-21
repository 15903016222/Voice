/**
 * @file network_menu.cpp
 * @brief network menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "network_menu.h"
#include "label_menu_item.h"

namespace DplPreferenceMenu {

NetworkMenu::NetworkMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* IP Address menu item */
    m_ipItem = new LabelMenuItem;
    m_ipItem->set(tr("IP Address"), "192.168.1.1");
//    connect(m_ipItem, SIGNAL(clicked()), this, SLOT(show_ip_address_dialog()));

    /* Subnet Mask menu item */
    m_maskItem = new LabelMenuItem;
    m_maskItem->set(tr("Subnet Mask"), "255.255.255.0");
//    connect(m_maskItem, SIGNAL(clicked()), this, SLOT(show_subnet_mask_dialog()));
}

NetworkMenu::~NetworkMenu()
{
    delete m_ipItem;
    delete m_maskItem;
}

void NetworkMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_ipItem);
    ui->menuItem1->layout()->addWidget(m_maskItem);
    m_ipItem->show();
    m_maskItem->show();
}

void NetworkMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_ipItem);
    ui->menuItem1->layout()->removeWidget(m_maskItem);
    m_ipItem->hide();
    m_maskItem->hide();
}

}
