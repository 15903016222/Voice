/**
 * @file receiver_menu.cpp
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "receiver_menu.h"


#include <ut/global_transceiver.h>

namespace DplUtSettingMenu {

ReceiverMenu::ReceiverMenu(QWidget *parent) :
    BaseMenu(parent),
    m_receiverItem(new SpinMenuItem(this, tr("Receiver"))),
    m_filterItem(new ComboMenuItem(this, tr("Filter"))),
    m_rectifierItem(new ComboMenuItem(this, tr("Rectifier"))),
    m_videoFilterItem(new ComboMenuItem(this, tr("Video Filter"))),
    m_averagingItem(new ComboMenuItem(this, tr("Averaging"))),
    m_dampingItem(new ComboMenuItem(this, tr("Damping")))
{
    m_layout0->addWidget(m_receiverItem);
    m_layout1->addWidget(m_filterItem);
    m_layout2->addWidget(m_rectifierItem);
    m_layout3->addWidget(m_videoFilterItem);
    m_layout4->addWidget(m_averagingItem);
    m_layout5->addWidget(m_dampingItem);

    m_receiverItem->set(1, 113, 0);
    connect(m_receiverItem,
            SIGNAL(value_changed(double)),
            this,
            SLOT(do_receiverItem_changed(double)));

    connect(m_filterItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_filterItem_changed(int)));

    m_videoFilterItem->set(s_onOff);
    connect(m_videoFilterItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_videoFilterItem_changed(int)));

    m_averagingItem->add_item(tr("1"));
    m_averagingItem->add_item(tr("2"));
    m_averagingItem->add_item(tr("4"));
    m_averagingItem->add_item(tr("8"));
    m_averagingItem->add_item(tr("16"));
    connect(m_averagingItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_averagingItem_changed(int)));

    m_dampingItem->add_item(tr("50Ω"));
    m_dampingItem->add_item(tr("200Ω"));
    connect(m_dampingItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_dampingItem_changed(int)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

void ReceiverMenu::do_receiverItem_changed(double val)
{
    DplFocallaw::ProbePointer probe = m_group->focallawer()->probe();
    if (!probe.isNull() && probe->is_pa()) {
        probe.staticCast<DplFocallaw::PaProbe>()->set_receiver_index(val-1);
    }
}

void ReceiverMenu::do_filterItem_changed(int index)
{
    DplUt::TransceiverPointer transceiver = m_group->transceiver();

    switch (index) {
    case 0:
        transceiver->set_filter(0);
        break;
    case 1:
        transceiver->set_filter(m_group->focallawer()->probe()->freq()*1000);
        break;
    case 2:
        transceiver->set_filter(1000);
        break;
    case 3:
        transceiver->set_filter(2500);
        break;
    case 4:
        transceiver->set_filter(5000);
        break;
    case 5:
        transceiver->set_filter(7500);
        break;
    case 6:
        transceiver->set_filter(20000);
        break;
    default:
        break;
    }
}

void ReceiverMenu::do_rectifierItem_changed(int index)
{
    if ( m_group->transceiver()->mode() == DplUt::Transceiver::TOFD ) {
        m_group->transceiver()->set_rectifier(static_cast<DplFpga::Group::Rectifier>(index));
    } else {
        m_group->transceiver()->set_rectifier(static_cast<DplFpga::Group::Rectifier>(index+1));
    }
}

void ReceiverMenu::do_videoFilterItem_changed(int index)
{
    m_group->transceiver()->set_video_filter(!index);
}

void ReceiverMenu::do_averagingItem_changed(int index)
{
    m_group->transceiver()->set_averaging(static_cast<DplFpga::Group::Averaging>(index));
}

void ReceiverMenu::do_dampingItem_changed(int index)
{
    if (m_group->mode() == DplDevice::Group::PA
            || m_group->mode() == DplDevice::Group::UT) {
        return;
    }

    DplUt::GlobalTransceiver::UtChannel channel = DplUt::GlobalTransceiver::UT_1;
    if (m_group->mode() == DplDevice::Group::UT2) {
        channel = DplUt::GlobalTransceiver::UT_2;
    }

    if (index == 0) {
        DplUt::GlobalTransceiver::instance()->set_tx_damping(channel, DplFpga::Fpga::R50);
    } else if (index == 1) {
        DplUt::GlobalTransceiver::instance()->set_tx_damping(channel, DplFpga::Fpga::R200);
    }
}

void ReceiverMenu::update(const DplDevice::GroupPointer &grp)
{
    /* disconnect */
    if (m_group) {
        disconnect(static_cast<DplUt::Transceiver *>(m_group->transceiver().data()),
                   SIGNAL(mode_changed(DplUt::Transceiver::Mode)),
                   this,
                   SLOT(update_rectifierItem()));
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(mode_changed(DplDevice::Group::Mode)),
                   this,
                   SLOT(update_dampingItem()));
    }

    m_group = grp;
    update_filterItem();
    update_receiverItem();

    connect(static_cast<DplUt::Transceiver *>(m_group->transceiver().data()),
            SIGNAL(mode_changed(DplUt::Transceiver::Mode)),
            this,
            SLOT(update_rectifierItem()));
    update_rectifierItem();

    m_videoFilterItem->set_current_index(!m_group->transceiver()->video_filter());
    m_averagingItem->set_current_index(m_group->transceiver()->averaging());

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(mode_changed(DplDevice::Group::Mode)),
            this,
            SLOT(update_dampingItem()));
    update_dampingItem();
}

void ReceiverMenu::update_filterItem()
{
    QStringList msgs;

    msgs.append(tr("none"));
    msgs.append(tr("Auto"));
    if (m_group->focallawer()->probe()->is_pa()) {
        msgs.append("1M");
        msgs.append("1.5M-2.5M");
        msgs.append("3-5M");
        msgs.append("7.5M");
    } else {
        msgs.append("1-2M");
        msgs.append("2-3M");
        msgs.append("3-6M");
        msgs.append("6-10M");
    }
    msgs.append(">=10M");
    m_filterItem->set(msgs);
    m_filterItem->set_current_index(1);
}

void ReceiverMenu::update_receiverItem()
{
    DplFocallaw::ProbePointer probe = m_group->focallawer()->probe();
    if (!probe.isNull() && probe->is_pa()) {
        m_receiverItem->set_value(probe.staticCast<DplFocallaw::PaProbe>()->receiver_index());
    } else {
        m_receiverItem->set_value(1);
    }
}

void ReceiverMenu::update_rectifierItem()
{
    disconnect(m_rectifierItem,
               SIGNAL(value_changed(int)),
               this,
               SLOT(do_rectifierItem_changed(int)));

    m_rectifierItem->clear();
    if ( m_group->transceiver()->mode() == DplUt::Transceiver::TOFD ) {
        m_rectifierItem->add_item(tr("RF"));
    }
    m_rectifierItem->add_item(tr("HW+"));
    m_rectifierItem->add_item(tr("HW-"));
    m_rectifierItem->add_item(tr("FW"));

    if ( m_group->transceiver()->mode() == DplUt::Transceiver::TOFD ) {
        m_rectifierItem->set_current_index(m_group->transceiver()->rectifier());
    } else {
        m_rectifierItem->set_current_index(m_group->transceiver()->rectifier()-1);
    }

    connect(m_rectifierItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_rectifierItem_changed(int)));
}

void ReceiverMenu::update_dampingItem()
{
    if (m_group->mode() == DplDevice::Group::PA
            || m_group->mode() == DplDevice::Group::UT) {
        m_dampingItem->hide();
        return;
    }

    DplFpga::Fpga::DampingType dampingType = DplFpga::Fpga::R50;
    if (m_group->mode() == DplDevice::Group::UT1) {
        dampingType = DplUt::GlobalTransceiver::instance()->tx_damping(DplUt::GlobalTransceiver::UT_1);
    } else {
        dampingType = DplUt::GlobalTransceiver::instance()->tx_damping(DplUt::GlobalTransceiver::UT_2);
    }

    if (dampingType == DplFpga::Fpga::R50) {
        m_dampingItem->set_current_index(0);
    } else if (dampingType == DplFpga::Fpga::R200) {
        m_dampingItem->set_current_index(1);
    }

    m_dampingItem->show();
}

}
