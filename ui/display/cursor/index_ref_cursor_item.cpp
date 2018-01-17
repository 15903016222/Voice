#include "index_ref_cursor_item.h"

IndexRefCursorItem::IndexRefCursorItem(const DplMeasure::CursorPointer &cursor,
                                     Qt::Orientation orientation) :
    IndexCursorItem(cursor, orientation, Qt::darkRed)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(index_reference_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(index_reference_changed(double)),
            this, SLOT(set_text(double)));
    set_text(cursor->index_reference());
}

void IndexRefCursorItem::position_event()
{
    if (!moving()) {
        return;
    }
    cursor()->set_index_reference(value());
}

double IndexRefCursorItem::ratio() const
{
    return (cursor()->index_reference() - visual_start()) / visual_range();
}

