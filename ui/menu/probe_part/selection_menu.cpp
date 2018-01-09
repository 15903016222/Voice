/**
 * @file probe_selection_menu.cpp
 * @brief Probe/Part Select Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#include "selection_menu.h"

#include "probe_dialog.h"
#include "wedge_dialog.h"

namespace DplProbeMenu {

SelectionMenu::SelectionMenu(QWidget *parent) :
    BaseMenu(parent),
    m_groupItem(new ComboMenuItem(this, tr("Group"))),
    m_modeItem(new ComboMenuItem(this, tr("Mode"))),
    m_probeItem(new LabelMenuItem(this, tr("Probe"))),
    m_wedgeItem(new LabelMenuItem(this, tr("Wedge"))),
    m_autoDetectItem(new ComboMenuItem(this, tr("Auto Detect")))
{
    m_layout0->addWidget(m_groupItem);
    m_layout1->addWidget(m_modeItem);
    m_layout2->addWidget(m_probeItem);
    m_layout3->addWidget(m_wedgeItem);
    m_layout4->addWidget(m_autoDetectItem);

    QStringList groupList;

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
    m_groupItem->set(groupList);

    m_modeItem->add_item("UT", tr("PA Connector"));
    m_modeItem->add_item("PA", tr("Phassed Array"));
    m_modeItem->add_item("UT1", tr("Conventional UT"));
    m_modeItem->add_item("UT2", tr("Conventional UT"));

    connect(m_modeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_groupModeItem_changed(int)));

    connect(m_probeItem, SIGNAL(clicked()),
            this, SLOT(do_probeItem_clicked()));

    connect(m_wedgeItem, SIGNAL(clicked()),
            this, SLOT(do_wedgeItem_clicked()));

    m_autoDetectItem->set(s_onOff);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void SelectionMenu::do_probeItem_clicked()
{
    ProbeDialog probeDialog;
    if (QDialog::Rejected == probeDialog.exec()) {
        return;
    }

    DplFocallaw::ProbePointer probePtr = probeDialog.get_probe();
    if (probePtr.isNull()) {
        m_probeItem->set_text("");
    } else {
        m_probeItem->set_text(probePtr->model());
        m_group->focallawer()->set_probe(probePtr);
    }
}

void SelectionMenu::do_wedgeItem_clicked()
{
    WedgeDialog wedgeDialog;
    if (QDialog::Rejected == wedgeDialog.exec()) {
        return;
    }

    DplFocallaw::WedgePointer wedgePointer = m_group->focallawer()->wedge();

    if (wedgePointer->load(wedgeDialog.get_path())) {
        m_wedgeItem->set_text(wedgePointer->model());
    }
}

void SelectionMenu::do_groupModeItem_changed(int index)
{
    m_group->set_mode(static_cast<DplDevice::Group::Mode>(index));
}

void SelectionMenu::update(const DplDevice::GroupPointer &group)
{
    m_group = group;

    m_modeItem->set_current_index(m_group->mode());
}

}
