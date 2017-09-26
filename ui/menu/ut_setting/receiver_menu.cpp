/**
 * @file receiver_menu.cpp
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "receiver_menu.h"
#include "ui_base_menu.h"

namespace DplUtSettingMenu {

ReceiverMenu::ReceiverMenu(QWidget *parent) :
    BaseMenu(parent),
    m_receiverItem(new LabelMenuItem(this, tr("Receiver"))),
    m_filterItem(new ComboMenuItem(this, tr("Filter"))),
    m_rectifierItem(new ComboMenuItem(this, tr("Rectifier"))),
    m_videoFilterItem(new ComboMenuItem(this, tr("Video Filter"))),
    m_averagingItem(new ComboMenuItem(this, tr("Averaging")))
{
    ui->layout0->addWidget(m_receiverItem);
    ui->layout1->addWidget(m_filterItem);
    ui->layout2->addWidget(m_rectifierItem);
    ui->layout3->addWidget(m_videoFilterItem);
    ui->layout4->addWidget(m_averagingItem);

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

    m_filterItem->set(filtersList);

    m_rectifierItem->set(rectifiersList);

    m_videoFilterItem->set(s_onOff);

    m_averagingItem->set(averagingsList);
}

ReceiverMenu::~ReceiverMenu()
{
}

}
