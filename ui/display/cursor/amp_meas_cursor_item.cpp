#include "amp_meas_cursor_item.h"
#include <QGraphicsView>

AmpMeasCursorItem::AmpMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                                   Qt::Orientation orientation) :
    AmpCursorItem(cursor, orientation, Qt::darkGreen)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_measurement_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_measurement_changed(double)),
            this, SLOT(set_text(double)));

    set_text(cursor->amplitude_measurement());
}

void AmpMeasCursorItem::position_event()
{
    if (!moving()) {
        return;
    }

    cursor()->set_amplitude_measurement(value());
}

double AmpMeasCursorItem::ratio() const
{
    return cursor()->amplitude_measurement() / 100;
}
