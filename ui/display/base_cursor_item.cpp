#include "base_cursor_item.h"
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QDebug>

BaseCursorItem::BaseCursorItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_movingFlag(false),
    m_position(-m_size.width() / 2.0)
{
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

    painter->setBrush(QBrush(Qt::red));

    QPointF point1(-m_size.width() / 2.0,
                   -m_size.height() / 2.0);

    QPointF point2(-m_size.width() / 2.0,
                   m_size.height());

    painter->drawLine(point1, point2);

    painter->drawRect(-m_size.width() / 2.0,
                      -m_size.height() / 2.0,
                      DEFAULT_TOOLTIP_WIDTH,
                      DEFAULT_TOOLTIP_HEIGHT);


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

        newPos.setY(0.0);

        qDebug() << "new x = " << newPos.x() << " Y = " << newPos.y()
                 << " rect x = " << boundingRect().x()
                 << " y = " << boundingRect().y()
                 << " w = " << boundingRect().width()
                 << " h = " << boundingRect().height();


        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}
