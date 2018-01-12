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

    if (orientation() == Qt::Horizontal) {
        cursor()->set_amplitude_measurement(
                    (scene()->sceneRect().bottom() - pos().y())
                    /scene()->sceneRect().height() * 100);
    } else {
        cursor()->set_amplitude_measurement(
                    (pos().x() - scene()->sceneRect().left())
                    /scene()->sceneRect().width() * 100);
    }
}

double AmpMeasCursorItem::ratio() const
{
    return cursor()->amplitude_measurement() / 100;
}
