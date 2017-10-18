/**
 * @file pulser_menu.cpp
 * @brief UT Setting Pulser Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#include "pulser_menu.h"
#include "ui_base_menu.h"

#include <ut/global_pulser.h>

namespace DplUtSettingMenu {

PulserMenu::PulserMenu(QWidget *parent) :
    BaseMenu(parent),
    m_txrxModeItem(new ComboMenuItem(this, tr("Tx/Rx Mode"))),
    m_pulserItem(new SpinMenuItem(this, tr("Pulser"))),
    m_voltageItem(new ComboMenuItem(this, tr("Voltage"))),
    m_pwItem(new SpinMenuItem(this, tr("PW"), "ns")),
    m_prfItem(new ComboMenuItem(this, tr("PRF"))),
    m_userDefItem(new SpinMenuItem(this, tr("User Def.")))
{
    ui->layout0->addWidget(m_txrxModeItem);
    ui->layout1->addWidget(m_pulserItem);
    ui->layout2->addWidget(m_voltageItem);
    ui->layout3->addWidget(m_pwItem);
    ui->layout4->addWidget(m_prfItem);
    ui->layout5->addWidget(m_userDefItem);

    m_userDefItem->hide();

    m_voltageItem->add_item("50V");
    m_voltageItem->add_item("100V");
    m_voltageItem->add_item("200V");
    connect(m_voltageItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_voltageItem_changed(int)));

    m_prfItem->add_item(tr("Auto Max"));
    m_prfItem->add_item(tr("Max/2"));
    m_prfItem->add_item(tr("Optimum"));
    m_prfItem->add_item(tr("UserDef"));
    connect(m_prfItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_prfItem_changed(int)));

    m_pulserItem->set(1, 113, 0);
    connect(m_pulserItem,
            SIGNAL(value_changed(double)),
            this,
            SLOT(do_pulserItem_changed(double)));

    m_pwItem->set(30, 1000, 1);
    connect(m_pwItem,
            SIGNAL(value_changed(double)),
            this,
            SLOT(do_pwItem_changed(double)));

    connect(DplUt::GlobalPulser::instance(),
            SIGNAL(prf_changed()),
            this,
            SLOT(update_userDefItem()));

    connect(m_userDefItem,
            SIGNAL(value_changed(double)),
            this,
            SLOT(do_userDevItem_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void PulserMenu::update_voltageItem()
{
    switch (DplUt::GlobalPulser::instance()->voltage(
                m_group->focallawer()->probe()->is_pa())) {
    case DplUt::GlobalPulser::V50:
        m_voltageItem->set_current_index(0);
        break;
    case DplUt::GlobalPulser::V100:
        m_voltageItem->set_current_index(1);
        break;
    case DplUt::GlobalPulser::V200:
        m_voltageItem->set_current_index(2);
        break;
    case DplUt::GlobalPulser::V400:
        m_voltageItem->set_current_index(3);
        break;
    default:
        break;
    }
}

void PulserMenu::do_txrxModeItem_changed(int index)
{
    m_group->pulser()->set_tx_rx_mode(static_cast<DplUt::Pulser::TxRxMode>(index));
}

void PulserMenu::do_pulserItem_changed(double val)
{
    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();
    probe->set_pulser_index(val);
}

void PulserMenu::do_voltageItem_changed(int index)
{
    DplUt::GlobalPulser::Voltage v = DplUt::GlobalPulser::V50;
    switch (index) {
    case 1:
        v = DplUt::GlobalPulser::V100;
        break;
    case 2:
        v = DplUt::GlobalPulser::V200;
        break;
    case 3:
        v = DplUt::GlobalPulser::V400;
        break;
    default:
        break;
    }
    DplUt::GlobalPulser::instance()->set_voltage(
                m_group->focallawer()->probe()->is_pa(),
                v);
}

void PulserMenu::do_pwItem_changed(double val)
{
    m_group->pulser()->set_pw(val);
}

void PulserMenu::do_prfItem_changed(int index)
{
    if (index == DplUt::GlobalPulser::USER_DEF) {
        m_userDefItem->show();
    } else {
        m_userDefItem->hide();
    }
    DplUt::GlobalPulser::instance()->set_prf_mode(static_cast<DplUt::GlobalPulser::PrfMode>(index));
}

void PulserMenu::do_userDevItem_changed(double val)
{
    DplUt::GlobalPulser::instance()->set_acquisition_rate(val);
}

void PulserMenu::update(const DplDevice::GroupPointer &group)
{
    m_group = group;

    update_txrxModeItem();
    m_pulserItem->set_value(m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>()->pulser_index());
    update_voltageItem();
    m_pwItem->set_value(m_group->pulser()->pw());
    m_prfItem->set_current_index(DplUt::GlobalPulser::instance()->prf_mode());
    update_userDefItem();
}

void PulserMenu::update_userDefItem()
{
    m_userDefItem->set_range(1, DplUt::GlobalPulser::instance()->max_acquisition_rate());
    m_userDefItem->set_value(DplUt::GlobalPulser::instance()->acquisition_rate());
}

void PulserMenu::update_txrxModeItem()
{
    disconnect(m_txrxModeItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_txrxModeItem_changed(int)));

    m_txrxModeItem->add_item(tr("PE"));
    m_txrxModeItem->add_item(tr("PC"));
    m_txrxModeItem->add_item(tr("TT"));
    if (m_group->mode() != DplDevice::Group::PA) {
        m_txrxModeItem->add_item(tr("TOFD"));
    }
    m_txrxModeItem->set_current_index(m_group->pulser()->tx_rx_mode());

    connect(m_txrxModeItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_txrxModeItem_changed(int)));

}


}
