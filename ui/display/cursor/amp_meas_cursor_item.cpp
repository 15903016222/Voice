#include "amp_meas_cursor_item.h"
#include <QGraphicsView>

AmpMeasCursorItem::AmpMeasCursorItem(const DplMeasure::CursorPointer &cursor,
                                   Qt::Orientation orientation) :
    CursorItem(cursor, orientation, Qt::darkGreen)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_measurement_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_measurement_changed(double)),
            this, SLOT(set_text(double)));
    connect(this, SIGNAL(size_changed()),
            this, SLOT(update_position()));
    connect(this, SIGNAL(xChanged()),
            this, SLOT(do_position_changed()));
    connect(this, SIGNAL(yChanged()),
            this, SLOT(do_position_changed()));

    set_text(cursor->amplitude_measurement());
}

void AmpMeasCursorItem::update_position()
{
    if (moving()
            || !scene()
            || scene()->views().isEmpty()) {
        return;
    }

    if (orientation() == Qt::Horizontal) {
        setPos(scene()->sceneRect().left(),
               scene()->sceneRect().bottom()
               - scene()->sceneRect().height() * cursor()->amplitude_measurement() / 100);
    } else {
        setPos(scene()->sceneRect().left()
               + scene()->sceneRect().width() * cursor()->amplitude_measurement() / 100,
               scene()->sceneRect().top());
    }
}

void AmpMeasCursorItem::do_position_changed()
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

void AmpMeasCursorItem::set_text(double val)
{
    CursorItem::set_text(QString::number(val,'f', 1));
}
