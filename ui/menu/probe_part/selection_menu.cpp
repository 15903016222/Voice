/**
 * @file probe_selection_menu.cpp
 * @brief Probe/Part Select Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#include "selection_menu.h"
#include "label_menu_item.h"

namespace DplProbeMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Label,
    MenuItem::Label,
    MenuItem::Combo,
    MenuItem::Combo
};

class SelectionMenuprivate
{
public:
    SelectionMenuprivate() {}
    LabelMenuItem *m_probeMenuItem;
    LabelMenuItem *m_wedgeMenuItem;
};

SelectionMenu::SelectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent),
    d(new SelectionMenuprivate)
{
    QStringList groupList;
    QStringList modeList;
    QStringList defineList;

    groupList.append(tr("Add"));
    groupList.append("1");
    groupList.append("2");
    groupList.append("3");
    groupList.append("4");
    groupList.append("5");
    groupList.append("6");
    groupList.append("7");
    groupList.append("8");
    groupList.append(tr("Remove"));

    modeList.append(tr("UT (PA Connector)"));
    modeList.append(tr("PA (Phassed Array)"));
    modeList.append(tr("UT1 (Conventional UT)"));
    modeList.append(tr("UT2 (Conventional UT)"));

    defineList.append(tr("Probe"));
    defineList.append(tr("Wedge"));

    m_menuItem[0]->set(tr("Group"), groupList);
    m_menuItem[1]->set(tr("Group Mode"), modeList);

    d->m_probeMenuItem = static_cast<LabelMenuItem *>(m_menuItem[2]);
    d->m_probeMenuItem->set(tr("Probe"), "");
    connect(d->m_probeMenuItem, SIGNAL(clicked()), this, SLOT(do_probeItem_clicked()));

    d->m_wedgeMenuItem = static_cast<LabelMenuItem *>(m_menuItem[3]);
    d->m_wedgeMenuItem->set(tr("Wedge"), "");
    connect(d->m_wedgeMenuItem, SIGNAL(clicked()), this, SLOT(do_wedgeItem_clicked()));

    m_menuItem[4]->set(tr("Define"), defineList);

    m_menuItem[5]->set(tr("Auto Detect"), s_onOff);

}

void SelectionMenu::do_probeItem_clicked()
{
//    ProbeDialog probeDialog;
//    probeDialog.exec();
//    QString string = probeDialog.get_current_item_text();
//    if(!string.isEmpty()){
//    }
}

void SelectionMenu::do_wedgeItem_clicked()
{
//    WedgeDialog wedgeDialog;
//    wedgeDialog.exec();
//    QString string = wedgeDialog.get_current_item_text();
//    if(!string.isEmpty()){
//    }
}

}
