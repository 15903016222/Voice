#include "index_meas_menu_item.h"

IndexMeasMenuItem::IndexMeasMenuItem(QWidget *parent) :
    IndexMenuItem(parent, "I(m)")
{
    update_group();
}

void IndexMeasMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
               SIGNAL(index_measurement_changed(double)),
               this, SLOT(set_value(double)));
    disconnect(this, SIGNAL(value_changed(double)),
               static_cast<DplMeasure::Cursor *>(cursor.data()),
               SLOT(set_index_measurement(double)));
}

void IndexMeasMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    set_value(cursor->index_measurement());

    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(index_measurement_changed(double)),
            this, SLOT(set_value(double)));
    connect(this, SIGNAL(value_changed(double)),
            static_cast<DplMeasure::Cursor *>(cursor.data()),
            SLOT(set_index_measurement(double)));
}
