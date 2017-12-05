/**
 * @file tcg_menu.cpp
 * @brief Gate/Curves tcg menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "tcg_menu.h"

#include <device/device.h>
#include <ui/tool/tool.h>

namespace DplGateCurvesMenu {

TcgMenu::TcgMenu(QWidget *parent) :
    BaseMenu(parent),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_modeItem(new ComboMenuItem(this, tr("Mode"))),
    m_curveNoItem(new SpinMenuItem(this, tr("Curve No."))),
    m_curveXItem(new ComboMenuItem(this, tr("Curve X"))),
    m_dbOffsetItem(new SpinMenuItem(this, tr("dB Offset"), tr("dB"))),
    m_pointItem(new ComboMenuItem(this, tr("Point"))),
    m_positionItem(new SpinMenuItem(this, tr("Position"))),
    m_gainItem(new SpinMenuItem(this, tr("Gain"), tr("dB"))),
    m_addPointItem(new LabelMenuItem(this, tr("Add Point"))),
    m_deletePointItem(new LabelMenuItem(this, tr("Delete Point")))
{
    m_layout0->addWidget(m_switchItem);
    m_layout1->addWidget(m_modeItem);

    /* Setting */
    m_layout2->addWidget(m_curveNoItem);
    m_layout3->addWidget(m_curveXItem);
    m_layout4->addWidget(m_dbOffsetItem);

    /* Edit */
    m_layout2->addWidget(m_pointItem);
    m_layout3->addWidget(m_positionItem);
    m_layout4->addWidget(m_gainItem);
    m_layout5->addWidget(m_addPointItem);
    m_layout6->addWidget(m_deletePointItem);

    m_modeItem->add_item(tr("Settings"));
    m_modeItem->add_item(tr("Edit"));
    connect(m_modeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_modeItem_changed(int)));

    /* Setting */
    m_curveNoItem->set(1, 5, 0);

    m_curveXItem->add_item("1");
    m_curveXItem->add_item("2");
    m_curveXItem->add_item("3");
    m_curveXItem->add_item("4");
    m_curveXItem->add_item("5");

    m_dbOffsetItem->set(-40, 40, 1);

    m_switchItem->set(s_onOff);
    connect(m_switchItem, SIGNAL(value_changed(int)),
            this, SLOT(do_switchItem_changed(int)));

    /* Edit */    
    m_positionItem->set_step(0.01);
    m_positionItem->set_decimals(2);

    m_gainItem->set(0, 40, 1, 0.1);
    connect(m_gainItem,
            SIGNAL(value_changed(double)),
            this,
            SLOT(do_gainItem_changed(double)));
    connect(m_addPointItem,
            SIGNAL(clicked()),
            this,
            SLOT(do_addPointItem_clicked()));
    connect(m_deletePointItem,
            SIGNAL(clicked()),
            this,
            SLOT(do_deletePointItem_clicked()));

    do_modeItem_changed(0);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void TcgMenu::do_modeItem_changed(int pos)
{
    if (pos == 0) {
        m_pointItem->hide();
        m_positionItem->hide();
        m_gainItem->hide();
        m_addPointItem->hide();
        m_deletePointItem->hide();

        m_curveNoItem->show();
        m_curveXItem->show();
        m_dbOffsetItem->show();
    } else {
        m_curveNoItem->hide();
        m_curveXItem->hide();
        m_dbOffsetItem->hide();

        m_pointItem->show();
        m_positionItem->show();
        m_gainItem->show();
        m_addPointItem->show();
        m_deletePointItem->show();
    }
}

void TcgMenu::do_switchItem_changed(int pos)
{
    m_group->tcgs()->set_enable(!pos);
}

void TcgMenu::do_pointItem_changed(int val)
{
    if (val == 0) {
        m_gainItem->setDisabled(true);
    } else {
        m_gainItem->setDisabled(false);
    }
    m_group->tcgs()->set_current_point(val);
}

void TcgMenu::do_positionItem_changed(double val)
{
    m_group->tcgs()->set_position(Tool::display_to_cnf(m_group,val));
}

void TcgMenu::do_gainItem_changed(double val)
{
    m_group->tcgs()->set_gain(val);
}

void TcgMenu::do_addPointItem_clicked()
{
    m_group->tcgs()->add_point();
    update_pointItem();
}

void TcgMenu::do_deletePointItem_clicked()
{
    m_group->tcgs()->delete_point();
    update_pointItem();
}

void TcgMenu::do_current_beam_changed(int index)
{
    m_group->tcgs()->set_current_tcg(index);
    update_pointItem();
}

void TcgMenu::update(const DplDevice::GroupPointer &group)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(current_beam_changed(int)),
                   this,
                   SLOT(do_current_beam_changed(int)));

        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
                   this,
                   SLOT(update_positionItem()));

        disconnect(static_cast<DplSizing::Tcgs *>(m_group->tcgs().data()),
                   SIGNAL(changed()),
                   this,
                   SLOT(update_pointItem()));
        disconnect(static_cast<DplSizing::Tcgs *>(m_group->tcgs().data()),
                   SIGNAL(current_point_changed()),
                   this,
                   SLOT(update_positionItem()));
        disconnect(static_cast<DplSizing::Tcgs *>(m_group->tcgs().data()),
                   SIGNAL(current_point_changed()),
                   this,
                   SLOT(update_gainItem()));
    }

    m_group = group;

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(current_beam_changed(int)),
            this,
            SLOT(do_current_beam_changed(int)));
    do_current_beam_changed(m_group->current_beam_index());

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_positionItem()));

    connect(static_cast<DplSizing::Tcgs *>(m_group->tcgs().data()),
            SIGNAL(changed()),
            this,
            SLOT(update_pointItem()));
    connect(static_cast<DplSizing::Tcgs *>(m_group->tcgs().data()),
            SIGNAL(current_point_changed()),
            this,
            SLOT(update_positionItem()));
    connect(static_cast<DplSizing::Tcgs *>(m_group->tcgs().data()),
            SIGNAL(current_point_changed()),
            this,
            SLOT(update_gainItem()));

    update_switchItem();
    update_pointItem();
}

void TcgMenu::update_switchItem()
{
    m_switchItem->set_current_index(!m_group->tcgs()->enable());
}

void TcgMenu::update_pointItem()
{
    disconnect(m_pointItem,
               SIGNAL(value_changed(int)),
               this,
               SLOT(do_pointItem_changed(int)));

    m_pointItem->set(QStringList());
    for (int i = 1; i <= m_group->tcgs()->point_count(); ++i) {
        m_pointItem->add_item(QString::number(i));
    }
    m_pointItem->set_current_index(m_group->tcgs()->current_point_index());

    connect(m_pointItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_pointItem_changed(int)));
}

void TcgMenu::update_positionItem()
{
    disconnect(m_positionItem,
               SIGNAL(value_changed(double)),
               this,
               SLOT(do_positionItem_changed(double)));

    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_positionItem->set_unit("us");
    } else {
        m_positionItem->set_unit("mm");
    }

    m_positionItem->set_range(Tool::cnf_to_display(m_group, m_group->sample()->start()),
                        Tool::cnf_to_display(m_group, m_group->sample()->start()+m_group->sample()->range()));

    m_positionItem->set_value(Tool::cnf_to_display(m_group,
                                                   m_group->tcgs()->position()));

    connect(m_positionItem,
            SIGNAL(value_changed(double)),
            this,
            SLOT(do_positionItem_changed(double)));
}

void TcgMenu::update_gainItem()
{
    m_gainItem->set_value(m_group->tcgs()->gain());
}

}
