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

#include <QDebug>

static const int GATE_HEIGHT = 4;

GateItem::GateItem(const QColor &color, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_width(50),
    m_color(color)
{
}

QRectF GateItem::boundingRect() const
{
//    qreal adjust = 0.5;
    return QRectF(0, -GATE_HEIGHT/2, m_width, GATE_HEIGHT);
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

void GateItem::set_geometry(const QRectF &rect)
{
    m_width = rect.width();
}

void GateItem::set_start(qreal start)
{
    if (!scene()) {
        return;
    }

    if (scene()->views().isEmpty()) {
        return;
    }
    QGraphicsView *view = scene()->views().first();
    QPointF pointF = view->mapToScene(0, 0);

    setPos(pointF.x(), pointF.y() + 1);
}

void GateItem::set_height(int height)
{
//    setPos();
}
