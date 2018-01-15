#include "index_ref_menu_item.h"

IndexRefMenuItem::IndexRefMenuItem(QWidget *parent) :
    IndexMenuItem(parent, "I(r)")
{
    update_group();
}

void IndexRefMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
               SIGNAL(index_reference_changed(double)),
               this, SLOT(set_value(double)));
    disconnect(this, SIGNAL(value_changed(double)),
               static_cast<DplMeasure::Cursor *>(cursor.data()),
               SLOT(set_index_reference(double)));
}

void IndexRefMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    set_value(cursor->index_reference());

    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(index_reference_changed(double)),
            this, SLOT(set_value(double)));
    connect(this, SIGNAL(value_changed(double)),
            static_cast<DplMeasure::Cursor *>(cursor.data()),
            SLOT(set_index_reference(double)));
}
