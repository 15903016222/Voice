#include "fft_menu.h"

#include "../menu_item/gain_menu_item.h"

#include <device/device.h>
#include <QMessageBox>
#include <source/source.h>
#include <ui/tool/tool.h>
#include <ut/sample.h>

namespace DplProbeMenu {

FftMenu::FftMenu(QWidget *parent) :
    BaseMenu(parent),
    m_gainItem(new GainMenuItem(this)),
    m_startItem(new SpinMenuItem(this, tr("Start"), "mm")),
    m_widthItem(new SpinMenuItem(this, tr("Width"), "mm")),
    m_switchItem(new ComboMenuItem(this, tr("Switch"))),
    m_currentGroupPointer(DplDevice::Device::instance()->current_group())
{
    m_layout0->addWidget(m_gainItem);
    m_layout1->addWidget(m_startItem);
    m_layout2->addWidget(m_widthItem);
    m_layout3->addWidget(m_switchItem);

    /* Start menu item */
    m_startItem->set(0, 16000, 2);
    m_startItem->set_value(Tool::cnf_to_display(m_currentGroupPointer,
                                                m_currentGroupPointer->gate_a()->start()));

    /* Width menu item */
    m_widthItem->set(0.05, 525, 2);
    m_widthItem->set_value(Tool::cnf_to_display(m_currentGroupPointer,
                                                m_currentGroupPointer->gate_a()->width()));

    /* Switch menu item */
    m_switchItem->set(s_onOff);
    m_switchItem->set_current_index(1); /* 0:On, 1:Off */

    init_connection();
}

FftMenu::~FftMenu()
{
}


void FftMenu::do_switchItem_changed(int val)
{
    DplDisplay::DisplayPointer  displayPointer = DplDevice::Device::instance()->display();
    if(val) {
        displayPointer->set_layout(DplDisplay::Display::A, displayPointer->grps());
    } else {
        /* TODO */
#if 0
        if(m_currentGroupPointer->transceiver()->rectifier() == DplFpga::Group::RF
                && (1 == (m_currentGroupPointer->sample()->range() / 10.0 / m_currentGroupPointer->current_beam()->point_qty()))) {
            displayPointer->set_layout(DplDisplay::Display::AFFT, displayPointer->grps());
        } else {
            QMessageBox::warning(this, tr("Warning"), "Range is too large Or Not RF mode.");
            disconnect(m_switchItem, SIGNAL(value_changed(int)), this, SLOT(do_switchItem_changed(int)));
            m_switchItem->set_current_index(!val);
            connect(m_switchItem, SIGNAL(value_changed(int)), this, SLOT(do_switchItem_changed(int)));
        }
#else
        displayPointer->set_layout(DplDisplay::Display::AFFT, displayPointer->grps());
#endif
    }
}


void FftMenu::do_current_group_changed(const DplDevice::GroupPointer &groupPointer)
{
    disconnect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(width_changed(float)),
            this, SLOT(do_width_changed(float)));
    disconnect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(start_changed(float)),
            this, SLOT(do_start_changed(float)));

    m_currentGroupPointer = groupPointer;

    connect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(width_changed(float)),
            this, SLOT(do_width_changed(float)));
    connect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(start_changed(float)),
            this, SLOT(do_start_changed(float)));

}


void FftMenu::do_start_changed(float val)
{
    disconnect(m_startItem, SIGNAL(value_changed(double)), this, SLOT(do_startItem_value_changed(double)));
    m_startItem->set_range(Tool::cnf_to_display(m_currentGroupPointer,
                                                m_currentGroupPointer->sample()->start()),
                           Tool::cnf_to_display(m_currentGroupPointer,
                                                m_currentGroupPointer->sample()->start()
                                                + m_currentGroupPointer->sample()->range()));
    m_startItem->set_value(Tool::cnf_to_display(m_currentGroupPointer, val));
    connect(m_startItem, SIGNAL(value_changed(double)), this, SLOT(do_startItem_value_changed(double)));
}


void FftMenu::do_width_changed(float val)
{
    disconnect(m_widthItem, SIGNAL(value_changed(double)), this, SLOT(do_widthItem_value_changed(double)));
    m_widthItem->set(Tool::cnf_to_display(m_currentGroupPointer, 0),
                     Tool::cnf_to_display(m_currentGroupPointer, m_currentGroupPointer->sample()->range()),
                     2, 0.01);
    m_widthItem->set_value(Tool::cnf_to_display(m_currentGroupPointer, val));
    connect(m_widthItem, SIGNAL(value_changed(double)), this, SLOT(do_widthItem_value_changed(double)));
}


void FftMenu::do_startItem_value_changed(double val)
{
    disconnect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(start_changed(float)),
            this, SLOT(do_start_changed(float)));
    m_currentGroupPointer->gate_a()->set_start(Tool::display_to_cnf(m_currentGroupPointer, val));
    connect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(start_changed(float)),
            this, SLOT(do_start_changed(float)));
}


void FftMenu::do_widthItem_value_changed(double val)
{
    disconnect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(width_changed(float)),
            this, SLOT(do_width_changed(float)));
    m_currentGroupPointer->gate_a()->set_width(Tool::display_to_cnf(m_currentGroupPointer, val));
    connect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(width_changed(float)),
            this, SLOT(do_width_changed(float)));
}

void FftMenu::init_connection()
{
    /* Gate start、end连接 */
    connect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(width_changed(float)),
            this, SLOT(do_width_changed(float)));
    connect(static_cast<DplGate::Gate *>(m_currentGroupPointer->gate_a().data()), SIGNAL(start_changed(float)),
            this, SLOT(do_start_changed(float)));

    /* Gate start、end Item连接 */
    connect(m_startItem, SIGNAL(value_changed(double)), this, SLOT(do_startItem_value_changed(double)));
    connect(m_widthItem, SIGNAL(value_changed(double)), this, SLOT(do_widthItem_value_changed(double)));

    /* FFT Switch item连接 */
    connect(m_switchItem, SIGNAL(value_changed(int)), this, SLOT(do_switchItem_changed(int)));

    /* 当前组连接 */
    connect(DplDevice::Device::instance(), SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));
}

}
