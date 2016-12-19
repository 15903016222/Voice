/**
 * @file tcg_menu.cpp
 * @brief Gate/Curves tcg menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "tcg_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"

static const MenuItem::Type s_typs[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Combo,
    MenuItem::Label
};

TcgMenu::TcgMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, s_typs, parent)
{
    QStringList modeList;
    QStringList curveXList;
    QStringList pointList;

    modeList.append(tr("Settings"));
    modeList.append(tr("Edit"));

    curveXList.append("1");
    curveXList.append("2");
    curveXList.append("3");
    curveXList.append("4");
    curveXList.append("5");

    pointList.append("1");
    pointList.append("2");

    m_settingFlag = true;

    m_menuItem[0]->set(tr("Mode"), modeList);
    connect(m_menuItem[0], SIGNAL(value_changed(int)), this, SLOT(do_mode_event(int)));

    m_menuItem[1]->set(tr("Curve No."), "", 1, 5, 0);
    m_menuItem[2]->set(tr("Curve X"), curveXList);
    m_menuItem[3]->set(tr("dB Offset"), "dB", -40, 40, 1);
    m_menuItem[4]->set(tr("Switch"), s_onOff);

    m_pointItem = new ComboMenuItem();
    m_positionItem = new SpinMenuItem();
    m_gainItem = new SpinMenuItem();
    m_addPointItem = new LabelMenuItem();
    m_deletePointItem = new LabelMenuItem();

    m_pointItem->set(tr("Point"), pointList);
    m_positionItem->set(tr("Position"), "", 0, 10000, 2);
    m_gainItem->set(tr("Gain"), "dB", 0, 100, 1);
    m_addPointItem->set(tr("Add Point"), "");
    m_deletePointItem->set(tr("Delete Point"), "");
}

void TcgMenu::show()
{
    if (m_settingFlag) {
        BaseMenu::show();
    } else {
        show_edit();
    }
}

void TcgMenu::hide()
{
    if (m_settingFlag) {
        BaseMenu::hide();
    } else {
        hide_edit();
    }
}

void TcgMenu::show_edit()
{
    ui->menuItem0->layout()->addWidget(m_menuItem[0]);
    ui->menuItem1->layout()->addWidget(m_pointItem);
    ui->menuItem2->layout()->addWidget(m_positionItem);
    ui->menuItem3->layout()->addWidget(m_gainItem);
    ui->menuItem4->layout()->addWidget(m_addPointItem);
    ui->menuItem5->layout()->addWidget(m_deletePointItem);

    m_menuItem[0]->show();
    m_pointItem->show();
    m_positionItem->show();
    m_gainItem->show();
    m_addPointItem->show();
    m_deletePointItem->show();
}

void TcgMenu::hide_edit()
{
    ui->menuItem0->layout()->removeWidget(m_menuItem[0]);
    ui->menuItem1->layout()->removeWidget(m_pointItem);
    ui->menuItem2->layout()->removeWidget(m_positionItem);
    ui->menuItem3->layout()->removeWidget(m_gainItem);
    ui->menuItem4->layout()->removeWidget(m_addPointItem);
    ui->menuItem5->layout()->removeWidget(m_deletePointItem);

    m_menuItem[0]->hide();
    m_pointItem->hide();
    m_positionItem->hide();
    m_gainItem->hide();
    m_addPointItem->hide();
    m_deletePointItem->hide();
}

void TcgMenu::do_mode_event(int pos)
{
    if (pos == 0) {
        m_settingFlag = true;
        hide_edit();
        BaseMenu::show();
    } else {
        m_settingFlag = false;
        BaseMenu::hide();
        show_edit();
    }
}
