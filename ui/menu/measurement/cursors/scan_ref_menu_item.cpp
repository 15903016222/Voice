#include "scan_ref_menu_item.h"

ScanRefMenuItem::ScanRefMenuItem(QWidget *parent) :
    ScanMenuItem(parent, "S(r)")
{
    update_group();
}

void ScanRefMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
               SIGNAL(scan_reference_changed(double)),
               this, SLOT(set_value(double)));
    disconnect(this, SIGNAL(value_changed(double)),
               static_cast<DplMeasure::Cursor *>(cursor.data()),
               SLOT(set_scan_reference(double)));
}

void ScanRefMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    set_value(cursor->scan_reference());

    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(scan_reference_changed(double)),
            this, SLOT(set_value(double)));
    connect(this, SIGNAL(value_changed(double)),
            static_cast<DplMeasure::Cursor *>(cursor.data()),
            SLOT(set_scan_reference(double)));
}
