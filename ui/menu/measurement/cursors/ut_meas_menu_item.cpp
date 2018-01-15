#include "ut_meas_menu_item.h"

#include "../../../tool/tool.h"

UtMeasMenuItem::UtMeasMenuItem(QWidget *parent) :
    UtMenuItem(parent, "U(m)")
{
    connect(this, SIGNAL(value_changed(double)),
            this, SLOT(do_value_changed(double)));

    update_group();
}

void UtMeasMenuItem::update_value()
{
    set_value(Tool::cnf_to_display(group(),
                                   group()->cursor()->ultrasound_measurement()));
}

void UtMeasMenuItem::do_value_changed(double val)
{
    group()->cursor()->set_ultrasound_measurement(Tool::display_to_cnf(group(),
                                                                       val));
}

void UtMeasMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
               SIGNAL(ultrasound_measurement_changed(double)),
               this, SLOT(update_value()));
}

void UtMeasMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(ultrasound_measurement_changed(double)),
            this, SLOT(update_value()));
}
