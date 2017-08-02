/**
 * @file gate_item.cpp
 * @brief 闸门项
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#include "gate_item.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>

#include <QDebug>

static const int GATE_HEIGHT = 4;

GateItem::GateItem(const DplGate::GatePointer &gate, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_gate(gate),
    m_ratio(1),
    m_movingFlag(false)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges); // 启动itemChanged()
    setZValue(1);

    connect(static_cast<DplGate::Gate *>(m_gate.data()),
            SIGNAL(visible_changed(bool)),
            this, SLOT(do_visible_changed(bool)));
    connect(static_cast<DplGate::Gate *>(m_gate.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_pos()));
    connect(static_cast<DplGate::Gate *>(m_gate.data()),
            SIGNAL(height_changed(int)),
            this, SLOT(update_pos()));

    do_visible_changed(m_gate->is_visible());
}

QRectF GateItem::boundingRect() const
{
//    qreal adjust = 0.5;
    return QRectF(0, -GATE_HEIGHT/2 - 10,
                  m_gate->width() * ratio(), GATE_HEIGHT + 20);
}

void GateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(m_gate->color());
    painter->drawLine(0, -GATE_HEIGHT/2, 0, GATE_HEIGHT/2);
    painter->drawLine(m_gate->width() * ratio(), -GATE_HEIGHT/2,
                      m_gate->width() * ratio(), GATE_HEIGHT/2);
    painter->drawLine(0, 0,
                      m_gate->width() * ratio(), 0);
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
        }

        m_gate->set_start((newPos.x() - rect.left())/ratio());
        m_gate->set_height((rect.bottom() - newPos.y()) / rect.height() * 100);

        return newPos;
    }
    return QGraphicsObject::itemChange(change, value);
}

void GateItem::do_visible_changed(bool flag)
{
    setVisible(flag);
}

void GateItem::update_pos()
{
    if (is_moving()) {
        return;
    }

    if (scene() && !scene()->views().isEmpty()) {
        setPos(scene()->sceneRect().left() + m_gate->start() * ratio(),
               scene()->sceneRect().bottom() - scene()->sceneRect().height() * m_gate->height() / 100);
    }
}
