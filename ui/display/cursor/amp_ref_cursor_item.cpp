#include "amp_ref_cursor_item.h"
#include <QGraphicsView>

AmpRefCursorItem::AmpRefCursorItem(const DplMeasure::CursorPointer &cursor,
                                   Qt::Orientation orientation) :
    AmpCursorItem(cursor, orientation, Qt::darkRed)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_reference_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_reference_changed(double)),
            this, SLOT(set_text(double)));

    set_text(cursor->amplitude_reference());
}

void AmpRefCursorItem::position_event()
{
    if (!moving()) {
        return;
    }

    cursor()->set_amplitude_reference(value());
}

double AmpRefCursorItem::ratio() const
{
    return cursor()->amplitude_reference() / 100;
}
