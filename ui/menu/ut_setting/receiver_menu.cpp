/**
 * @file receiver_menu.cpp
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "receiver_menu.h"

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Label,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Label
};

ReceiverMenu::ReceiverMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, s_types, parent)
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

    m_menuItem[0]->set(tr("Receiver"), "");
    m_menuItem[1]->set(tr("Filter"), filtersList);
    m_menuItem[2]->set(tr("Rectifier"), rectifiersList);
    m_menuItem[3]->set(tr("Video Filter"), s_onOff);
    m_menuItem[4]->set(tr("Averaging"), averagingsList);
}


