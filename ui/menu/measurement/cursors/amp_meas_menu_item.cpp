/**
 * @file amp_meas_menu_item.cpp
 * @brief 幅值测量菜单
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2018-01-11
 */
#include "amp_meas_menu_item.h"

AmpMeasMenuItem::AmpMeasMenuItem(QWidget *parent) :
    CursorMenuItem(parent, "%(m)")
{
    set(0, 100, 1, 0.1);

    update_group();
}

void AmpMeasMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
               SIGNAL(amplitude_measurement_changed(double)),
               this, SLOT(set_value(double)));
    disconnect(this, SIGNAL(value_changed(double)),
               static_cast<DplMeasure::Cursor *>(cursor.data()),
               SLOT(set_amplitude_measurement(double)));
}

void AmpMeasMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    set_value(cursor->amplitude_reference());

    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_measurement_changed(double)),
            this, SLOT(set_value(double)));
    connect(this, SIGNAL(value_changed(double)),
            static_cast<DplMeasure::Cursor *>(cursor.data()),
            SLOT(set_amplitude_measurement(double)));
}
