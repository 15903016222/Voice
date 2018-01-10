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
