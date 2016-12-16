#include "alarm_menu.h"

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Label
};

AlarmMenu::AlarmMenu(Ui::SubMenu *ui, QObject *parent)
    : BaseMenu(ui, s_types, parent)
{
    QStringList alarmList;
    QStringList groupList;
    QStringList conditionList;
    QStringList operatorList;

    alarmList.append(tr("Alarm 1"));
    alarmList.append(tr("Alarm 2"));
    alarmList.append(tr("Alarm 3"));

    groupList.append(tr("Group1"));
    groupList.append(tr("All"));
    groupList.append(tr("None"));

    conditionList.append(tr("None"));
    conditionList.append(tr("Gate A"));
    conditionList.append(tr("Gate B"));
    conditionList.append(tr("Gate I"));
    conditionList.append(tr("Not Gate A"));
    conditionList.append(tr("Not Gate B"));
    conditionList.append(tr("Not Gate I"));
    conditionList.append(tr(">Max.Thickness"));
    conditionList.append(tr("<Min.Thickness"));

    operatorList.append(tr("And"));
    operatorList.append(tr("Or"));


    m_menuItem[0]->set(tr("Alarm"), alarmList);
    m_menuItem[1]->set(tr("Switch"), s_onOff);
    m_menuItem[2]->set(tr("Group"), groupList);
    m_menuItem[3]->set(tr("Condition"), conditionList);
    m_menuItem[4]->set(tr("Operator"), operatorList);
}
