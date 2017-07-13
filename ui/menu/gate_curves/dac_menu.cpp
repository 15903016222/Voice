/**
 * @file dac_menu.cpp
 * @brief dac menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "dac_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"
#include "label_menu_item.h"

namespace DplGateCurvesMenu {

DacMenu::DacMenu(Ui::BaseMenu *ui, QObject *parent)
    : BaseMenu(ui, parent)
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

    m_modeItem.set(tr("Mode"), modeList);
    connect(&m_modeItem, SIGNAL(value_changed(int)), this, SLOT(do_mode_event(int)));

    m_curveNoItem.set(tr("Curve No."), "", 1, 5, 0);

    m_curveXItem.set(tr("Curve X"), curveXList);

    m_dbOffsetItem.set(tr("dB Offset"), "dB", -40, 40, 1);

    m_refGainItem.set(tr("Ref.Gain"), "dB", -40, 40, 1);

    m_switchItem.set(tr("Switch"), s_onOff);

    m_pointItem.set(tr("Point"), pointList);
    m_positionItem.set(tr("Position"), "",  0, 10000, 2);
    m_addPointItem.set(tr("Add Point"), "");
    m_deletePointItem.set(tr("Delete Point"), "");
}

DacMenu::~DacMenu()
{
}

void DacMenu::show()
{
    if (m_modeItem.current_index() == 0) {
        show_setting();
    } else {
        show_edit();
    }
}

void DacMenu::hide()
{
    if (m_modeItem.current_index() == 0) {
        hide_setting();
    } else {
        hide_edit();
    }
}

void DacMenu::show_setting()
{
    ui->menuItem0->layout()->addWidget(&m_modeItem);
    ui->menuItem1->layout()->addWidget(&m_curveNoItem);
    ui->menuItem2->layout()->addWidget(&m_curveXItem);
    ui->menuItem3->layout()->addWidget(&m_dbOffsetItem);
    ui->menuItem4->layout()->addWidget(&m_refGainItem);
    ui->menuItem5->layout()->addWidget(&m_switchItem);
    m_modeItem.show();
    m_curveNoItem.show();
    m_curveXItem.show();
    m_dbOffsetItem.show();
    m_refGainItem.show();
    m_switchItem.show();
}

void DacMenu::hide_setting()
{
    ui->menuItem0->layout()->removeWidget(&m_modeItem);
    ui->menuItem1->layout()->removeWidget(&m_curveNoItem);
    ui->menuItem2->layout()->removeWidget(&m_curveXItem);
    ui->menuItem3->layout()->removeWidget(&m_dbOffsetItem);
    ui->menuItem4->layout()->removeWidget(&m_refGainItem);
    ui->menuItem5->layout()->removeWidget(&m_switchItem);
    m_modeItem.hide();
    m_curveNoItem.hide();
    m_curveXItem.hide();
    m_dbOffsetItem.hide();
    m_refGainItem.hide();
    m_switchItem.hide();}

void DacMenu::show_edit()
{
    ui->menuItem0->layout()->addWidget(&m_modeItem);
    ui->menuItem1->layout()->addWidget(&m_pointItem);
    ui->menuItem2->layout()->addWidget(&m_positionItem);
    ui->menuItem3->layout()->addWidget(&m_addPointItem);
    ui->menuItem4->layout()->addWidget(&m_deletePointItem);
    m_modeItem.show();
    m_pointItem.show();
    m_positionItem.show();
    m_addPointItem.show();
    m_deletePointItem.show();
}

void DacMenu::hide_edit()
{
    ui->menuItem0->layout()->removeWidget(&m_modeItem);
    ui->menuItem1->layout()->removeWidget(&m_pointItem);
    ui->menuItem2->layout()->removeWidget(&m_positionItem);
    ui->menuItem3->layout()->removeWidget(&m_addPointItem);
    ui->menuItem4->layout()->removeWidget(&m_deletePointItem);
    m_modeItem.hide();
    m_pointItem.hide();
    m_positionItem.hide();
    m_addPointItem.hide();
    m_deletePointItem.hide();
}

void DacMenu::do_mode_event(int pos)
{
    if (pos == 0) {
        hide_edit();
        show_setting();
    } else {
        hide_setting();
        show_edit();
    }
}

}
