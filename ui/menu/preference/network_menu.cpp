/**
 * @file network_menu.cpp
 * @brief network menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#include "network_menu.h"
#include "label_menu_item.h"
#include "networkdialog.h"

namespace DplPreferenceMenu {

NetworkMenu::NetworkMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* IP Address menu item */
    m_ipItem = new LabelMenuItem;
    m_ipItem->set(tr("IP Address"), "192.168.1.1");
    connect(m_ipItem, SIGNAL(clicked()), this, SLOT(show_ip_address_dialog()));

    /* Subnet Mask menu item */
    m_maskItem = new LabelMenuItem;
    m_maskItem->set(tr("Subnet Mask"), "255.255.255.0");
    connect(m_maskItem, SIGNAL(clicked()), this, SLOT(show_subnet_mask_dialog()));
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

void NetworkMenu::show_ip_address_dialog()
{
    NetworkDialog *dialog = new NetworkDialog;
//    QMap<QString, QString> map;
//    map.insert("IP Address Set", m_ipItem->get_title());
    QString title = m_ipItem->get_title();
    QString str = m_ipItem->get_text();

    dialog->set_dialog_title(title);
    dialog->set_spinbox_value(str);

    if (dialog->exec() == NetworkDialog::Accepted) {
        m_ipItem->set_text(dialog->get_text());
    } else {
        m_ipItem->set_text(str);
    }
    delete dialog;
}

void NetworkMenu::show_subnet_mask_dialog()
{
    NetworkDialog *dialog = new NetworkDialog;
//    QMap<QString, QString> map;
//    map.insert("Subnet Mask Set", m_maskItem->get_title());
    QString title = m_maskItem->get_title();
    QString str = m_maskItem->get_text();

    dialog->set_dialog_title(title);
    dialog->set_spinbox_value(str);

    if (dialog->exec() == NetworkDialog::Accepted) {
        m_maskItem->set_text(dialog->get_text());
    } else {
        m_maskItem->set_text(str);
    }
    delete dialog;
}

}
