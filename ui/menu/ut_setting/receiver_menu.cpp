/**
 * @file receiver_menu.cpp
 * @brief UT Setting receiver menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "receiver_menu.h"
#include "ui_base_menu.h"

namespace DplUtSettingMenu {

ReceiverMenu::ReceiverMenu(QWidget *parent) :
    BaseMenu(parent),
    m_receiverItem(new SpinMenuItem(this, tr("Receiver"))),
    m_filterItem(new ComboMenuItem(this, tr("Filter"))),
    m_rectifierItem(new ComboMenuItem(this, tr("Rectifier"))),
    m_videoFilterItem(new ComboMenuItem(this, tr("Video Filter"))),
    m_averagingItem(new ComboMenuItem(this, tr("Averaging")))
{
    ui->layout0->addWidget(m_receiverItem);
    ui->layout1->addWidget(m_filterItem);
    ui->layout2->addWidget(m_rectifierItem);
    ui->layout3->addWidget(m_videoFilterItem);
    ui->layout4->addWidget(m_averagingItem);

    m_receiverItem->set(1, 113, 0);
    connect(m_receiverItem,
            SIGNAL(value_changed(double)),
            this,
            SLOT(do_receiverItem_changed(double)));

    connect(m_filterItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_filterItem_changed(int)));

    m_rectifierItem->add_item(tr("RF"));
    m_rectifierItem->add_item(tr("HW+"));
    m_rectifierItem->add_item(tr("HW-"));
    m_rectifierItem->add_item(tr("FW"));
    connect(m_rectifierItem,
            SIGNAL(value_changed(int)),
            this,
            SLOT(do_rectifierItem_changed(int)));

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
        probe.staticCast<DplFocallaw::PaProbe>()->set_receiver_index(val);
    }
}

void ReceiverMenu::do_filterItem_changed(int index)
{
    DplUt::ReceiverPointer receiver = m_group->receiver();

    switch (index) {
    case 0:
        receiver->set_filter(0);
        break;
    case 1:
        receiver->set_filter(m_group->focallawer()->probe()->freq()*1000);
        break;
    case 2:
        receiver->set_filter(1000);
        break;
    case 3:
        receiver->set_filter(2500);
        break;
    case 4:
        receiver->set_filter(5000);
        break;
    case 5:
        receiver->set_filter(7500);
        break;
    case 6:
        receiver->set_filter(20000);
        break;
    default:
        break;
    }
}

void ReceiverMenu::do_rectifierItem_changed(int index)
{
    m_group->receiver()->set_rectifier(static_cast<DplFpga::Group::Rectifier>(index));
}

void ReceiverMenu::do_videoFilterItem_changed(int index)
{
    m_group->receiver()->set_video_filter(!index);
}

void ReceiverMenu::do_averagingItem_changed(int index)
{
    m_group->receiver()->set_averaging(static_cast<DplFpga::Group::Averaging>(index));
}

void ReceiverMenu::update(const DplDevice::GroupPointer &grp)
{
    m_group = grp;
    update_filter_item();
    update_receiver_item();
    m_rectifierItem->set_current_index(m_group->receiver()->rectifier());
    m_videoFilterItem->set_current_index(!m_group->receiver()->video_filter());
    m_averagingItem->set_current_index(m_group->receiver()->averaging());
}

void ReceiverMenu::update_filter_item()
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

void ReceiverMenu::update_receiver_item()
{
    DplFocallaw::ProbePointer probe = m_group->focallawer()->probe();
    if (!probe.isNull() && probe->is_pa()) {
        m_receiverItem->set_value(probe.staticCast<DplFocallaw::PaProbe>()->receiver_index());
    } else {
        m_receiverItem->set_value(1);
    }
}

}
