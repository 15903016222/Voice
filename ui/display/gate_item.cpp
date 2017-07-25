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
    m_ratio(1),
    m_start(0),
    m_width(50),
    m_height(25),
    m_color(color)
{
    setFlag(QGraphicsItem::ItemIsMovable);
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

void GateItem::update_pos()
{
    if (scene() && !scene()->views().isEmpty()) {
        setPos(scene()->sceneRect().left() + m_start,
               scene()->sceneRect().bottom() - scene()->sceneRect().height() * m_height / 100);
    }
}
