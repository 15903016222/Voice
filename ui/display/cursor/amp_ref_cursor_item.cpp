#include "amp_ref_cursor_item.h"
#include <QGraphicsView>

AmpRefCursorItem::AmpRefCursorItem(const DplMeasure::CursorPointer &cursor,
                                   Qt::Orientation orientation) :
    CursorItem(cursor, orientation, Qt::darkRed)
{
    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(amplitude_reference_changed(double)),
            this, SLOT(update_position()));
    connect(this, SIGNAL(size_changed()),
            this, SLOT(update_position()));
    connect(this, SIGNAL(xChanged()),
            this, SLOT(do_position_changed()));
    connect(this, SIGNAL(yChanged()),
            this, SLOT(do_position_changed()));
}

void AmpRefCursorItem::update_position()
{
    if (moving()
            || !scene()
            || scene()->views().isEmpty()) {
        return;
    }

    prepareGeometryChange();
    qDebug("%s(%s[%d]): %f, %f, %f", __FILE__, __func__, __LINE__, cursor()->amplitude_reference(),
           scene()->sceneRect().bottom() - scene()->sceneRect().height() * cursor()->amplitude_reference() / 100,
           scene()->sceneRect().bottom());

    if (orientation() == Qt::Horizontal) {
        qDebug("%s(%s[%d]): ", __FILE__, __func__, __LINE__);
        setPos(scene()->sceneRect().left(),
               scene()->sceneRect().bottom()
               - scene()->sceneRect().height() * cursor()->amplitude_reference() / 100);
    } else {
        qDebug("%s(%s[%d]): ", __FILE__, __func__, __LINE__);
        setPos(scene()->sceneRect().left()
               + scene()->sceneRect().width() * cursor()->amplitude_reference() / 100,
               scene()->sceneRect().top());
    }
}

void AmpRefCursorItem::do_position_changed()
{
    if (!moving()) {
        return;
    }

    if (orientation() == Qt::Horizontal) {
        cursor()->set_amplitude_reference(
                    (scene()->sceneRect().bottom() - pos().y())
                    /scene()->sceneRect().height() * 100);
    } else {
        cursor()->set_amplitude_reference(
                    (pos().x() - scene()->sceneRect().left())
                    /scene()->sceneRect().width() * 100);
    }
}
