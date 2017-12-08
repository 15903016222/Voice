/**
 * @file dac_menu.cpp
 * @brief dac menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "dac_menu.h"


namespace DplGateCurvesMenu {

DacMenu::DacMenu(QWidget *parent) : BaseMenu(parent),
    m_switchItem(new ComboMenuItem(this, tr("DAC"))),
    m_modeItem(new ComboMenuItem(this, tr("Mode"))),
    m_curveNoItem(new SpinMenuItem(this, tr("Curve No."))),
    m_curveXItem(new ComboMenuItem(this, tr("Curve X"))),
    m_dbOffsetItem(new SpinMenuItem(this, tr("dB Offset"), tr("dB"))),
    m_refGainItem(new SpinMenuItem(this, tr("Ref Gain"), tr("dB"))),
    m_pointItem(new ComboMenuItem(this, tr("Point"))),
    m_positionItem(new SpinMenuItem(this, tr("Position"))),
    m_addPointItem(new LabelMenuItem(this, tr("Add Point"))),
    m_deletePointItem(new LabelMenuItem(this, tr("Delete Point")))
{
    m_layout0->addWidget(m_switchItem);
    m_layout1->addWidget(m_modeItem);

    /* Setting */
    m_layout2->addWidget(m_curveNoItem);
    m_layout3->addWidget(m_curveXItem);
    m_layout4->addWidget(m_dbOffsetItem);
    m_layout5->addWidget(m_refGainItem);

    /* Edit */
    m_layout2->addWidget(m_pointItem);
    m_layout3->addWidget(m_positionItem);
    m_layout4->addWidget(m_addPointItem);
    m_layout5->addWidget(m_deletePointItem);

    m_modeItem->add_item(tr("Settings"));
    m_modeItem->add_item(tr("Edit"));

    m_curveXItem->add_item("1");
    m_curveXItem->add_item("2");
    m_curveXItem->add_item("3");
    m_curveXItem->add_item("4");
    m_curveXItem->add_item("5");

    m_pointItem->add_item("1");

    connect(m_modeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_modeItem_changed(int)));

    m_curveNoItem->set(1, 5, 0);

    m_dbOffsetItem->set(-40, 40, 1);

    m_refGainItem->set(-40, 40, 1);

    m_switchItem->set(s_onOff);

    m_positionItem->set(0, 10000, 2);

    do_modeItem_changed(0);
}

DacMenu::~DacMenu()
{
}

void DacMenu::do_modeItem_changed(int pos)
{
    if (pos == 0) {
        m_pointItem->hide();
        m_positionItem->hide();
        m_addPointItem->hide();
        m_deletePointItem->hide();

        m_curveNoItem->show();
        m_curveXItem->show();
        m_dbOffsetItem->show();
        m_refGainItem->show();
    } else {
        m_curveNoItem->hide();
        m_curveXItem->hide();
        m_dbOffsetItem->hide();
        m_refGainItem->hide();

        m_pointItem->show();
        m_positionItem->show();
        m_addPointItem->show();
        m_deletePointItem->show();
    }
}

}
