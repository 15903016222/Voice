#include "vdisplay_cursor_item.h"
#include <QPainter>

VDisplayCursorItem::VDisplayCursorItem(Qt::Orientation cursorOrientation,
                                 BaseCursorItem::E_CURSOR_TYPE cursorType,
                                 QGraphicsItem *parent) :
    BaseCursorItem(cursorOrientation, cursorType, parent)
{

}

void VDisplayCursorItem::paint_cursor(QPainter *painter)
{
    QRectF rectF;
    QFont font;
    font.setPointSize(8);
    /* 指示框 */
    QColor color(205, 205, 205); /* 灰色 */
    rectF = QRectF(0.0, 0.0,
                BaseCursorItem::s_defaultTooltipWidth,
                BaseCursorItem::s_defaultTooltipHeight);

    painter->fillRect(rectF, QBrush(color));

    painter->setPen(QColor(Qt::black));
    painter->setFont(font);
    QString valueText;
    get_value(valueText);
    painter->drawText(rectF, valueText, QTextOption(Qt::AlignCenter));

    painter->setPen(m_color);
    QPointF startPoint(0.0, 0.0);

    if(Qt::Vertical == m_cursorOrientation) {
        QPointF endPoint(0.0, m_size.height());
        painter->drawLine(startPoint, endPoint);
    } else {
        QPointF endPoint(m_size.width(), 0.0);
        painter->drawLine(startPoint, endPoint);
    }
}


