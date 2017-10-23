#include "base_cursor_item.h"
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QDebug>

static const int    DEFAULT_TOOLTIP_WIDTH  = 25;
static const int    DEFAULT_TOOLTIP_HEIGHT = 13;

BaseCursorItem::BaseCursorItem(Qt::Orientation orientation, Qt::Orientation innerOrientation, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_movingFlag(false),
    m_color(Qt::red),
    m_orientation(orientation),
    m_innerOrientation(innerOrientation)
{
    if((m_orientation == Qt::Vertical && m_innerOrientation == Qt::Horizontal)
            || (m_innerOrientation == Qt::Vertical &&  m_orientation == Qt::Horizontal))
    {
        m_color = QColor(Qt::blue);
    }

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}


QRectF BaseCursorItem::boundingRect() const
{
    return QRectF(-m_size.width() / 2.0, -m_size.height() / 2.0,
                  m_size.width(), DEFAULT_TOOLTIP_HEIGHT);
}


void BaseCursorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    /* 指示框 */
    QColor color(205, 205, 205); /* 灰色 */

    QRectF rectF;
    QFont font;
    font.setPointSize(8);

    if(Qt::Vertical == m_orientation) {
        if(Qt::Horizontal == m_innerOrientation) {

            rectF = QRectF(-m_size.width() / 2.0,
                        -m_size.height() / 2.0,
                        DEFAULT_TOOLTIP_WIDTH,
                        DEFAULT_TOOLTIP_HEIGHT);

            painter->fillRect(rectF, QBrush(color));
            painter->setPen(QColor(Qt::black));
            painter->setFont(font);
            painter->drawText(rectF, QString::number(11.88),
                              QTextOption(Qt::AlignCenter));

            painter->setPen(m_color);
            QPointF point1(-m_size.width() / 2.0,
                           -m_size.height() / 2.0);

            QPointF point2(m_size.width() / 2.0,
                           -m_size.height() / 2.0);

            painter->drawLine(point1, point2);

        } else {

             rectF = QRectF(-m_size.width() / 2.0,
                         -m_size.height() / 2.0,
                         DEFAULT_TOOLTIP_WIDTH,
                         DEFAULT_TOOLTIP_HEIGHT);

             painter->fillRect(rectF, QBrush(color));
             painter->setPen(QColor(Qt::black));
             painter->setFont(font);
             painter->drawText(rectF, QString::number(11.88),
                               QTextOption(Qt::AlignCenter));

             painter->setPen(m_color);
             QPointF point1(-m_size.width() / 2.0,
                            -m_size.height() / 2.0);

             QPointF point2(-m_size.width() / 2.0,
                            m_size.height());

             painter->drawLine(point1, point2);

        }


    } else {
        if(Qt::Horizontal == m_innerOrientation) {

            rectF = QRectF(m_size.width() / 2.0 - DEFAULT_TOOLTIP_HEIGHT,
                         -m_size.height() / 2.0,
                         DEFAULT_TOOLTIP_HEIGHT,
                         DEFAULT_TOOLTIP_WIDTH);

            painter->fillRect(rectF, QBrush(color));
            painter->setPen(QColor(Qt::black));
            painter->setFont(font);
            /* 旋转90度 */
            painter->rotate(90);

            painter->drawText(QRectF(-m_size.height() / 2.0,
                                     -m_size.width() / 2.0,
                                     DEFAULT_TOOLTIP_WIDTH,
                                     DEFAULT_TOOLTIP_HEIGHT),
                              QString::number(11.88),
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
                         DEFAULT_TOOLTIP_HEIGHT,
                         DEFAULT_TOOLTIP_WIDTH);

            painter->fillRect(rectF, QBrush(color));
            painter->setPen(QColor(Qt::black));
            painter->setFont(font);
            /* 旋转90度 */
            painter->rotate(90);

            painter->drawText(QRectF(-m_size.height() / 2.0,
                                     m_size.width() / 2.0 - DEFAULT_TOOLTIP_HEIGHT,
                                     DEFAULT_TOOLTIP_WIDTH,
                                     DEFAULT_TOOLTIP_HEIGHT),
                              QString::number(11.88),
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
}

void BaseCursorItem::do_visible_changed(bool flag)
{
    setVisible(flag);
}

void BaseCursorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = true;
    QGraphicsItem::mousePressEvent(event);
}

void BaseCursorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant BaseCursorItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene() && m_movingFlag) {
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();

        if(!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));

            qDebug() << " contains......";
        }

        if(m_innerOrientation == Qt::Vertical) {
            newPos.setY(0.0);
        } else {
            newPos.setX(0.0);
        }

        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}
