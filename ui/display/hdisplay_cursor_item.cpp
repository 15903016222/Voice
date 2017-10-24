#include "hdisplay_cursor_item.h"
#include <QPainter>

HDisplayCursorItem::HDisplayCursorItem(Qt::Orientation cursorOrientation,
                                 BaseCursorItem::E_CURSOR_TYPE cursorType,
                                 BaseCursorItem::E_CURSOR_SOURCE_TYPE sourceType,
                                 const DplMeasure::CursorPointer &cursorPointer,
                                 QGraphicsItem *parent) :
    BaseCursorItem(cursorOrientation, cursorType, sourceType, cursorPointer, parent)
{

}


void HDisplayCursorItem::paint_cursor(QPainter *painter)
{
    /* 指示框 */
    QColor color(205, 205, 205); /* 灰色 */

    QRectF rectF;
    QFont font;
    font.setPointSize(8);

    if(Qt::Horizontal == m_cursorOrientation) {

        rectF = QRectF(m_size.width() / 2.0 - BaseCursorItem::s_defaultTooltipHeight,
                     -m_size.height() / 2.0,
                     BaseCursorItem::s_defaultTooltipHeight,
                     BaseCursorItem::s_defaultTooltipWidth);

        painter->fillRect(rectF, QBrush(color));
        painter->setPen(QColor(Qt::black));
        painter->setFont(font);
        /* 旋转90度 */
        painter->rotate(90);
        QString valueText;
        get_value(valueText);
        painter->drawText(QRectF(-m_size.height() / 2.0,
                                 -m_size.width() / 2.0,
                                 BaseCursorItem::s_defaultTooltipWidth,
                                 BaseCursorItem::s_defaultTooltipHeight),
                          valueText,
                          QTextOption(Qt::AlignCenter));

        painter->rotate(-90);

        painter->setPen(m_color);
        QPointF point1(-m_size.width() / 2.0,
                       -m_size.height() / 2.0);

        QPointF point2(m_size.width() / 2.0,
                       -m_size.height() / 2.0);

        painter->drawLine(point1, point2);

    } else {

        rectF = QRectF(-m_size.width() / 2.0,
                     -m_size.height() / 2.0,
                     BaseCursorItem::s_defaultTooltipHeight,
                     BaseCursorItem::s_defaultTooltipWidth);

        painter->fillRect(rectF, QBrush(color));
        painter->setPen(QColor(Qt::black));
        painter->setFont(font);
        /* 旋转90度 */
        painter->rotate(90);

        QString valueText;
        get_value(valueText);
        painter->drawText(QRectF(-m_size.height() / 2.0,
                                 m_size.width() / 2.0 - BaseCursorItem::s_defaultTooltipHeight,
                                 BaseCursorItem::s_defaultTooltipWidth,
                                 BaseCursorItem::s_defaultTooltipHeight),
                          valueText,
                          QTextOption(Qt::AlignCenter));

        painter->rotate(-90);

        painter->setPen(m_color);
        QPointF point1(-m_size.width() / 2.0,
                       -m_size.height() / 2.0);

        QPointF point2(-m_size.width() / 2.0,
                       m_size.height());

        painter->drawLine(point1, point2);
    }
}
