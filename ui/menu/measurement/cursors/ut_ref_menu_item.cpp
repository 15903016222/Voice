#include "ut_ref_menu_item.h"

#include "../../../tool/tool.h"

#include <device/device.h>

UtRefMenuItem::UtRefMenuItem(QWidget *parent) :
    UtMenuItem(parent, "U(r)")
{
    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    update_group();
}

void UtRefMenuItem::update_value()
{
    set_value(Tool::cnf_to_display(group(),
                                   group()->cursor()->ultrasound_reference()));
}

void UtRefMenuItem::do_value_changed(double val)
{
    group()->cursor()->set_ultrasound_reference(Tool::display_to_cnf(group(),
                                                                     val));
}

void UtRefMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
                   SIGNAL(ultrasound_reference_changed(double)),
               this, SLOT(update_value()));
}

void UtRefMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(ultrasound_reference_changed(double)),
            this, SLOT(update_value()));
}
