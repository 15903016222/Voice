#include "amp_cursor_item.h"
#include <QGraphicsView>

AmpCursorItem::AmpCursorItem(const DplMeasure::CursorPointer &cursor,
                             Qt::Orientation orientation,
                             QColor color) :
    CursorItem(cursor, orientation, color)
{
}

void AmpCursorItem::set_text(double val)
{
    CursorItem::set_text(QString::number(val, 'f', 1));
}

double AmpCursorItem::value() const
{
    if (orientation() == Qt::Horizontal) {
        if (direction() == NORMAL) {
            return (size().height() - pos().y()) / size().height() * 100;
        } else {
            return pos().y() / size().height() * 100;
        }
    } else {
        if (direction() == NORMAL) {
            return pos().x() / size().width() * 100;
        } else {
            return (size().width() - pos().x()) / size().width() * 100;
        }
    }
}
