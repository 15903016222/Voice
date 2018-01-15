#include "scan_ref_cursor_item.h"

ScanRefCursorItem::ScanRefCursorItem(const DplMeasure::CursorPointer &cursor,
                                     Qt::Orientation orientation) :
    ScanCursorItem(cursor, orientation, Qt::darkRed)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(scan_reference_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(scan_reference_changed(double)),
            this, SLOT(set_text(double)));
    set_text(cursor->scan_reference());
}

void ScanRefCursorItem::position_event()
{
    if (!moving()) {
        return;
    }
    cursor()->set_scan_reference(value());
}

double ScanRefCursorItem::ratio() const
{
    return (cursor()->scan_reference() - visual_start()) / visual_range();
}

