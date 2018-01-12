/**
 * @file gate_item.cpp
 * @brief 闸门项
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#include "vpa_item.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneDragDropEvent>

#include <QDebug>

static const int DEFAULT_WIDTH  = 4;

VpaItem::VpaItem(const DplDevice::GroupPointer &group) : QGraphicsObject(),
    m_movingFlag(false),
    m_group(group)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges); // 启动itemChanged()
    setZValue(1);

    connect(static_cast<DplDevice::Group *>(group.data()),
            SIGNAL(current_beam_changed(int)),
            this, SLOT(update_pos()));
}

QRectF VpaItem::boundingRect() const
{
    return QRectF(-DEFAULT_WIDTH/2 - 10, 0,
                  DEFAULT_WIDTH + 20, 500);
}

void VpaItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    painter->setPen(Qt::black);
    if (scene()) {
        painter->drawLine(0, 0,
                          0, scene()->sceneRect().height());
    }
}

void VpaItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = true;
    QGraphicsItem::mousePressEvent(event);
}

void VpaItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant VpaItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene() && m_movingFlag) {
        // value is the new position.
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();

        float step = rect.width() / m_group->focallawer()->beam_qty();

        int x = (newPos.x() - rect.left()) / step + 0.5;
        qDebug("%s[%d]: %d",__func__, __LINE__, x);

        newPos.setX(rect.left() + x*step);
        newPos.setY(rect.top());

        return newPos;
    }
    return QGraphicsObject::itemChange(change, value);
}

void VpaItem::do_visible_changed(bool flag)
{
    setVisible(flag);
}

void VpaItem::update_pos()
{
    if ( is_moving()
         ||m_group->mode() != DplDevice::Group::PA
         || !scene() || scene()->views().isEmpty()) {
        return;
    }

    DplFocallaw::PaProbePointer probe = m_group->focallawer()->probe().staticCast<DplFocallaw::PaProbe>();

    if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear
            && m_group->focallawer()->beam_qty() > 1) {
            setPos(scene()->sceneRect().left()+scene()->sceneRect().width() * m_group->current_beam_index() / (m_group->focallawer()->beam_qty()-1),
                   scene()->sceneRect().top());
    } else if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Sectorial) {
//        m_group->s_scan()->
        resetTransform();
        setTransform(QTransform().rotate(-30), true);
    }
}
