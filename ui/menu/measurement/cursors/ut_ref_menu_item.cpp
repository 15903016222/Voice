#include "ut_ref_menu_item.h"

#include "../../../tool/tool.h"

#include <device/device.h>

UtRefMenuItem::UtRefMenuItem(QWidget *parent) :
    UtMenuItem(parent, "U(r)")
{
    update_group();
}

void UtRefMenuItem::update_value()
{
    set_value(Tool::cnf_to_display(group(), m_cursor->ultrasound_reference()));
}

void UtRefMenuItem::do_value_changed(double val)
{
    m_cursor->set_ultrasound_reference(Tool::display_to_cnf(group(), val));
}

void UtRefMenuItem::cursor_change_event(const DplMeasure::CursorPointer &cursor)
{
    if (m_cursor) {
        disconnect(static_cast<DplMeasure::Cursor *>(m_cursor.data()),
                       SIGNAL(ultrasound_reference_changed(double)),
                       this, SLOT(update_value()));
        disconnect(this, SIGNAL(value_changed(double)),
                   this, SLOT(do_value_changed(double)));
    }

    m_cursor = cursor;

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));
    connect(static_cast<DplMeasure::Cursor *>(m_cursor.data()),
            SIGNAL(ultrasound_reference_changed(double)),
            this, SLOT(update_value()));
}
