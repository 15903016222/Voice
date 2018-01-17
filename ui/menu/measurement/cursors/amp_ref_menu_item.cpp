/**
 * @file amp_ref_menu_item.cpp
 * @brief 幅值参考菜单
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2018-01-11
 */
#include "amp_ref_menu_item.h"

AmpRefMenuItem::AmpRefMenuItem(QWidget *parent) :
    CursorMenuItem(parent, "%(r)")
{
    set(0, 100, 1, 0.1);

    update_group();
}

void AmpRefMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
               SIGNAL(amplitude_reference_changed(double)),
               this, SLOT(set_value(double)));
    disconnect(this, SIGNAL(value_changed(double)),
               static_cast<DplMeasure::Cursor *>(cursor.data()),
               SLOT(set_amplitude_reference(double)));

}

void AmpRefMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    set_value(cursor->amplitude_reference());

    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_reference_changed(double)),
            this, SLOT(set_value(double)));
    connect(this, SIGNAL(value_changed(double)),
            static_cast<DplMeasure::Cursor *>(cursor.data()),
            SLOT(set_amplitude_reference(double)));
}
