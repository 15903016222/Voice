#include "index_cursor_item.h"

#include <source/scan.h>

IndexCursorItem::IndexCursorItem(const DplMeasure::CursorPointer &cursor,
                               Qt::Orientation orientation,
                               QColor color) :
    AxisCursorItem(cursor, DplSource::Scan::instance()->index_axis(),
                   orientation, color, PaleGreenColor)
{

}
