/**
 * @file output_menu.cpp
 * @brief Gate/Curves ouput menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "output_menu.h"

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Spin,
    MenuItem::Label,
    MenuItem::Combo
};

OutputMenu::OutputMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, s_types, parent)
{
    QStringList outputList;
    QStringList soundList;
    QStringList dataList;

    outputList.append(tr("Alarm 1"));
    outputList.append(tr("Alarm 2"));
    outputList.append(tr("Alarm 3"));
    outputList.append(tr("Analog 1"));
    outputList.append(tr("Analog 2"));

    soundList.append(tr("Off No Sound"));
    soundList.append(tr("300Hz Audio Output at 300Hz"));
    soundList.append(tr("600Hz Audio Output at 600Hz"));
    soundList.append(tr("1000Hz Audio Output at 1000Hz"));
    soundList.append(tr("5000Hz Audio Output at 5000Hz"));

    dataList.append(tr("A%"));
    dataList.append(tr("B%"));
    dataList.append(tr("None"));

    m_menuItem[0]->set(tr("Output"), outputList);
    m_menuItem[1]->set(tr("Sound"), soundList);
    m_menuItem[2]->set(tr("Delay"), "mm", 0, 5000, 2);
    m_menuItem[3]->set(tr("Hold Time"), "%", 0, 5000, 2);
    m_menuItem[4]->set(tr("Group"), "");
    m_menuItem[5]->set(tr("Data"), dataList);
}
