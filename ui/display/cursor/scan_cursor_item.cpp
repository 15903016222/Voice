#include "scan_cursor_item.h"

#include <source/scan.h>

ScanCursorItem::ScanCursorItem(const DplMeasure::CursorPointer &cursor,
                               Qt::Orientation orientation,
                               QColor color) :
    AxisCursorItem(cursor, DplSource::Scan::instance()->scan_axis(),
                   orientation, color, DarkBlueColor)
{

}



