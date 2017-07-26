/**
 * @file gate_item.cpp
 * @brief 闸门项
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#include "gate_item.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>

#include <QDebug>

static const int GATE_HEIGHT = 4;

GateItem::GateItem(const QColor &color, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_ratio(1),
    m_start(0),
    m_width(50),
    m_height(25),
    m_color(color),
    m_movingFlag(false)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges); // 启动itemChanged()
    setZValue(1);
}

QRectF GateItem::boundingRect() const
{
//    qreal adjust = 0.5;
    return QRectF(0, -GATE_HEIGHT/2 - 10, m_width, GATE_HEIGHT + 20);
}

void GateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(m_color);
    painter->drawLine(0, -GATE_HEIGHT/2, 0, GATE_HEIGHT/2);
    painter->drawLine(m_width, -GATE_HEIGHT/2, m_width, GATE_HEIGHT/2);
    painter->drawLine(0, 0, m_width, 0);
}

void GateItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "Pos: " << event->pos();
    QGraphicsItem::dragMoveEvent(event);
}

void GateItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_start = pos().x() - scene()->sceneRect().left();
    m_height = (scene()->sceneRect().bottom() - pos().y()) / scene()->sceneRect().height() * 100;

    QGraphicsItem::mouseMoveEvent(event);

    emit pos_changed();
}

void GateItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = true;
    QGraphicsItem::mousePressEvent(event);
}

void GateItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant GateItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();
        if (!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
            return newPos;
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void GateItem::update_pos()
{
    if (scene() && !scene()->views().isEmpty()) {
        setPos(scene()->sceneRect().left() + m_start,
               scene()->sceneRect().bottom() - scene()->sceneRect().height() * m_height / 100);
    }
}
