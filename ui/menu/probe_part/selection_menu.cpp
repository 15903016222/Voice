/**
 * @file probe_selection_menu.cpp
 * @brief Probe/Part Select Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-19
 */
#include "selection_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"
#include "label_menu_item.h"

namespace DplProbeMenu {

SelectionMenu::SelectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    DplDevice::Device *dev = DplDevice::Device::get_instance();
    connect(dev, SIGNAL(current_group_changed()), this, SLOT(do_current_group_changed()));
    m_group = dev->current_group();

    m_groupItem = new ComboMenuItem;
    m_groupModeItem = new ComboMenuItem;
    m_probeItem = new LabelMenuItem;
    m_wedgeItem = new LabelMenuItem;
    m_defineItem = new ComboMenuItem;
    m_autoDetectItem = new ComboMenuItem;

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

    m_groupItem->set(tr("Group"), groupList);

    m_groupModeItem->set(tr("Group Mode"), modeList);
    connect(m_groupModeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_groupModeItem_changed(int)));

    m_probeItem->set(tr("Probe"), "");
    connect(m_probeItem, SIGNAL(clicked()), this, SLOT(do_probeItem_clicked()));

    m_wedgeItem->set(tr("Wedge"), "");
    connect(m_wedgeItem, SIGNAL(clicked()), this, SLOT(do_wedgeItem_clicked()));

    m_defineItem->set(tr("Define"), defineList);

    m_autoDetectItem->set(tr("Auto Detect"), s_onOff);

    m_updateFlag = true;
}

SelectionMenu::~SelectionMenu()
{
    delete m_groupItem;
    delete m_groupModeItem;
    delete m_probeItem;
    delete m_wedgeItem;
    delete m_defineItem;
    delete m_autoDetectItem;
}

void SelectionMenu::show()
{
    if (m_updateFlag) {
        update();
    }
    ui->menuItem0->layout()->addWidget(m_groupItem);
    ui->menuItem1->layout()->addWidget(m_groupModeItem);
    ui->menuItem2->layout()->addWidget(m_probeItem);
    ui->menuItem3->layout()->addWidget(m_wedgeItem);
    ui->menuItem4->layout()->addWidget(m_defineItem);
    ui->menuItem5->layout()->addWidget(m_autoDetectItem);
    m_groupItem->show();
    m_groupModeItem->show();
    m_probeItem->show();
    m_wedgeItem->show();
    m_defineItem->show();
    m_autoDetectItem->show();
}

void SelectionMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_groupItem);
    ui->menuItem1->layout()->removeWidget(m_groupModeItem);
    ui->menuItem2->layout()->removeWidget(m_probeItem);
    ui->menuItem3->layout()->removeWidget(m_wedgeItem);
    ui->menuItem4->layout()->removeWidget(m_defineItem);
    ui->menuItem5->layout()->removeWidget(m_autoDetectItem);
    m_groupItem->hide();
    m_groupModeItem->hide();
    m_probeItem->hide();
    m_wedgeItem->hide();
    m_defineItem->hide();
    m_autoDetectItem->hide();
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

void SelectionMenu::do_groupModeItem_changed(int index)
{
    m_group->set_mode(static_cast<DplDevice::Group::Mode>(index));
}

void SelectionMenu::do_current_group_changed()
{
    m_group = DplDevice::Device::get_instance()->current_group();
    if (m_probeItem->isHidden()) {
        m_updateFlag = true;
    } else {
        update();
    }
}

void SelectionMenu::update()
{
    m_groupModeItem->set_current_index(m_group->mode());

    m_updateFlag = false;
}

}
