#include "scan_meas_menu_item.h"

ScanMeasMenuItem::ScanMeasMenuItem(QWidget *parent) :
    ScanMenuItem(parent, "S(m)")
{
    update_group();
}

void ScanMeasMenuItem::disconnect_cursor(const DplMeasure::CursorPointer &cursor)
{
    disconnect(static_cast<DplMeasure::Cursor *>(cursor.data()),
               SIGNAL(scan_measurement_changed(double)),
               this, SLOT(set_value(double)));
    disconnect(this, SIGNAL(value_changed(double)),
               static_cast<DplMeasure::Cursor *>(cursor.data()),
               SLOT(set_scan_measurement(double)));
}

void ScanMeasMenuItem::connect_cursor(const DplMeasure::CursorPointer &cursor)
{
    set_value(cursor->scan_measurement());

    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(scan_measurement_changed(double)),
            this, SLOT(set_value(double)));
    connect(this, SIGNAL(value_changed(double)),
            static_cast<DplMeasure::Cursor *>(cursor.data()),
            SLOT(set_scan_measurement(double)));
}
