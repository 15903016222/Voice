/**
 * @file dac_menu.cpp
 * @brief dac menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "dac_menu.h"


namespace DplGateCurvesMenu {

DacMenu::DacMenu(QWidget *parent) :
    BaseMenu(parent),
    m_modeItem(new ComboMenuItem(this, tr("Mode"))),
    m_curveNoItem(new SpinMenuItem(this, tr("Curve No."))),
    m_curveXItem(new ComboMenuItem(this, tr("Curve X"))),
    m_dbOffsetItem(new SpinMenuItem(this, tr("dB Offset"), tr("dB"))),
    m_refGainItem(new SpinMenuItem(this, tr("Ref Gain"), tr("dB"))),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_pointItem(new ComboMenuItem(this, tr("Point"))),
    m_positionItem(new SpinMenuItem(this, tr("Position"))),
    m_addPointItem(new LabelMenuItem(this, tr("Add Point"))),
    m_deletePointItem(new LabelMenuItem(this, tr("Delete Point")))
{
    m_layout0->addWidget(m_modeItem);

    /* Setting */
    m_layout1->addWidget(m_curveNoItem);
    m_layout2->addWidget(m_curveXItem);
    m_layout3->addWidget(m_dbOffsetItem);
    m_layout4->addWidget(m_refGainItem);
    m_layout5->addWidget(m_switchItem);

    /* Edit */
    m_layout1->addWidget(m_pointItem);
    m_layout2->addWidget(m_positionItem);
    m_layout3->addWidget(m_addPointItem);
    m_layout4->addWidget(m_deletePointItem);

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

    m_modeItem->set(modeList);
    connect(m_modeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_modeItem_changed(int)));

    m_curveNoItem->set(1, 5, 0);

    m_curveXItem->set(curveXList);

    m_dbOffsetItem->set(-40, 40, 1);

    m_refGainItem->set(-40, 40, 1);

    m_switchItem->set(s_onOff);

    m_pointItem->set(pointList);
    m_positionItem->set(0, 10000, 2);

    do_modeItem_changed(0);
}

DacMenu::~DacMenu()
{
}

void DacMenu::show_setting()
{
    m_curveNoItem->show();
    m_curveXItem->show();
    m_dbOffsetItem->show();
    m_refGainItem->show();
    m_switchItem->show();
}

void DacMenu::hide_setting()
{
    m_curveNoItem->hide();
    m_curveXItem->hide();
    m_dbOffsetItem->hide();
    m_refGainItem->hide();
    m_switchItem->hide();
}

void DacMenu::show_edit()
{
    m_pointItem->show();
    m_positionItem->show();
    m_addPointItem->show();
    m_deletePointItem->show();
}

void DacMenu::hide_edit()
{
    m_pointItem->hide();
    m_positionItem->hide();
    m_addPointItem->hide();
    m_deletePointItem->hide();
}

void DacMenu::do_modeItem_changed(int pos)
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
