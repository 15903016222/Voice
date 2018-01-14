#include "scan_meas_cursor_item.h"

ScanMeasCursorItem::ScanMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                                     Qt::Orientation orientation) :
    ScanCursorItem(cursor, orientation, Qt::darkGreen)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(scan_measurement_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(scan_measurement_changed(double)),
            this, SLOT(set_text(double)));
    set_text(cursor->scan_measurement());
}

void ScanMeasCursorItem::position_event()
{
    if (!moving()) {
        return;
    }
    cursor()->set_scan_measurement(value());
}

double ScanMeasCursorItem::ratio() const
{
    return (cursor()->scan_measurement() - visual_start()) / visual_range();
}

