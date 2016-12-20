/**
 * @file receiver_menu.cpp
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "receiver_menu.h"
#include "label_menu_item.h"
#include "combo_menu_item.h"

ReceiverMenu::ReceiverMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
{
    QStringList filtersList;
    QStringList rectifiersList;
    QStringList averagingsList;

    filtersList.append(tr("none"));
    filtersList.append(tr("1M"));
    filtersList.append(tr("1.5M-2.5M"));
    filtersList.append(tr("3-5M"));
    filtersList.append(tr("7.5M"));
    filtersList.append(tr("more than 10M"));

    rectifiersList.append(tr("RF"));
    rectifiersList.append(tr("FW"));
    rectifiersList.append(tr("HW+"));
    rectifiersList.append(tr("HW-"));

    averagingsList.append(tr("1"));
    averagingsList.append(tr("2"));
    averagingsList.append(tr("4"));
    averagingsList.append(tr("8"));
    averagingsList.append(tr("16"));

    m_receiverItem = new LabelMenuItem();
    m_receiverItem->set(tr("Receiver"), "");

    m_filterItem = new ComboMenuItem;
    m_filterItem->set(tr("Filter"), filtersList);

    m_rectifierItem = new ComboMenuItem;
    m_rectifierItem->set(tr("Rectifier"), rectifiersList);

    m_videoFilterItem = new ComboMenuItem;
    m_videoFilterItem->set(tr("Video Filter"), s_onOff);

    m_averaginItem = new ComboMenuItem;
    m_averaginItem->set(tr("Averaging"), averagingsList);
}

ReceiverMenu::~ReceiverMenu()
{
    delete m_receiverItem;
    delete m_filterItem;
    delete m_rectifierItem;
    delete m_videoFilterItem;
    delete m_averaginItem;
}

void ReceiverMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_receiverItem);
    ui->menuItem1->layout()->addWidget(m_filterItem);
    ui->menuItem2->layout()->addWidget(m_rectifierItem);
    ui->menuItem3->layout()->addWidget(m_videoFilterItem);
    ui->menuItem4->layout()->addWidget(m_averaginItem);
    m_receiverItem->show();
    m_filterItem->show();
    m_rectifierItem->show();
    m_videoFilterItem->show();
    m_averaginItem->show();
}

void ReceiverMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_receiverItem);
    ui->menuItem1->layout()->removeWidget(m_filterItem);
    ui->menuItem2->layout()->removeWidget(m_rectifierItem);
    ui->menuItem3->layout()->removeWidget(m_videoFilterItem);
    ui->menuItem4->layout()->removeWidget(m_averaginItem);
    m_receiverItem->hide();
    m_filterItem->hide();
    m_rectifierItem->hide();
    m_videoFilterItem->hide();
    m_averaginItem->hide();
}


