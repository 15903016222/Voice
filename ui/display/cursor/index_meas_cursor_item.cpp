#include "index_meas_cursor_item.h"

IndexMeasCursorItem::IndexMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                                     Qt::Orientation orientation) :
    IndexCursorItem(cursor, orientation, Qt::darkRed)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(index_measurement_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(index_measurement_changed(double)),
            this, SLOT(set_text(double)));
    set_text(cursor->index_measurement());
}

void IndexMeasCursorItem::position_event()
{
    if (!moving()) {
        return;
    }
    cursor()->set_index_measurement(value());
}

double IndexMeasCursorItem::ratio() const
{
    return (cursor()->index_measurement() - visual_start()) / visual_range();
}

