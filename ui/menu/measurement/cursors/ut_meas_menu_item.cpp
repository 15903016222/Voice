#include "ut_meas_menu_item.h"

#include "../../../tool/tool.h"

UtMeasMenuItem::UtMeasMenuItem(QWidget *parent) :
    UtMenuItem(parent, "U(m)")
{
    update_group();
}

void UtMeasMenuItem::update_value()
{
    set_value(Tool::cnf_to_display(group(), m_cursor->ultrasound_measurement()));
}

void UtMeasMenuItem::do_value_changed(double val)
{
    m_cursor->set_ultrasound_measurement(Tool::display_to_cnf(group(), val));
}

void UtMeasMenuItem::cursor_change_event(const DplMeasure::CursorPointer &cursor)
{
    if (m_cursor) {
        disconnect(this, SIGNAL(value_changed(double)),
                   this, SLOT(do_value_changed(double)));
        disconnect(static_cast<DplMeasure::Cursor *>(m_cursor.data()),
                   SIGNAL(ultrasound_measurement_changed(double)),
                   this, SLOT(update_value()));
    }

    m_cursor = cursor;

    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));
    connect(static_cast<DplMeasure::Cursor *>(m_cursor.data()),
            SIGNAL(ultrasound_measurement_changed(double)),
            this, SLOT(update_value()));
}
