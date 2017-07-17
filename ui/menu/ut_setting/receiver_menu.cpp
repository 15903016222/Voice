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

namespace DplUtSettingMenu {

ReceiverMenu::ReceiverMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
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

    m_receiverItem.set(tr("Receiver"), "");

    m_filterItem.set(tr("Filter"), filtersList);

    m_rectifierItem.set(tr("Rectifier"), rectifiersList);

    m_videoFilterItem.set(tr("Video Filter"), s_onOff);

    m_averaginItem.set(tr("Averaging"), averagingsList);
}

ReceiverMenu::~ReceiverMenu()
{
}

void ReceiverMenu::show()
{
    ui->layout0->addWidget(&m_receiverItem);
    ui->layout1->addWidget(&m_filterItem);
    ui->layout2->addWidget(&m_rectifierItem);
    ui->layout3->addWidget(&m_videoFilterItem);
    ui->layout4->addWidget(&m_averaginItem);
    m_receiverItem.show();
    m_filterItem.show();
    m_rectifierItem.show();
    m_videoFilterItem.show();
    m_averaginItem.show();
}

void ReceiverMenu::hide()
{
    ui->layout0->removeWidget(&m_receiverItem);
    ui->layout1->removeWidget(&m_filterItem);
    ui->layout2->removeWidget(&m_rectifierItem);
    ui->layout3->removeWidget(&m_videoFilterItem);
    ui->layout4->removeWidget(&m_averaginItem);
    m_receiverItem.hide();
    m_filterItem.hide();
    m_rectifierItem.hide();
    m_videoFilterItem.hide();
    m_averaginItem.hide();
}

}
