/**
 * @file amp_meas_menu_item.cpp
 * @brief 幅值测量菜单
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2018-01-11
 */
#include "amp_meas_menu_item.h"
#include <device/device.h>

AmpMeasMenuItem::AmpMeasMenuItem(QWidget *parent) :
    SpinMenuItem(parent, "%(m)")
{
    set(0, 100, 1);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));

    do_group_changed(DplDevice::Device::instance()->current_group());
}

void AmpMeasMenuItem::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_cursor) {
        disconnect(static_cast<DplMeasure::Cursor *>(m_cursor.data()),
                   SIGNAL(amplitude_measurement_changed(double)),
                   this, SLOT(set_value(double)));
        disconnect(this, SIGNAL(value_changed(double)),
                   static_cast<DplMeasure::Cursor *>(m_cursor.data()),
                   SLOT(set_amplitude_measurement(double)));
    }

    m_cursor = group->cursor();
    set_value(m_cursor->amplitude_reference());

    connect(static_cast<DplMeasure::Cursor *>(m_cursor.data()),
            SIGNAL(amplitude_measurement_changed(double)),
            this, SLOT(set_value(double)));
    connect(this, SIGNAL(value_changed(double)),
            static_cast<DplMeasure::Cursor *>(m_cursor.data()),
            SLOT(set_amplitude_measurement(double)));
}
