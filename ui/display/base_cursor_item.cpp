#include "base_cursor_item.h"

#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QString>

const int BaseCursorItem::s_defaultTooltipWidth     = 30;
const int BaseCursorItem::s_defaultTooltipHeight    = 13;

BaseCursorItem::BaseCursorItem(Qt::Orientation cursorOrientation,
                               E_CURSOR_TYPE cursorType,
                               QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_cursorOrientation(cursorOrientation),
    m_cursorType(cursorType),
    m_movingFlag(false),
    m_visible(false)
{
    if(cursorType == BaseCursorItem::Reference) {
        m_color = QColor(Qt::blue);
    } else {
        m_color = QColor(Qt::red);
    }

    m_cursorInfo.currentValue = 0;
    m_cursorInfo.end          = 0;
    m_cursorInfo.start        = 0;
    m_cursorInfo.pos          = 0;

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setZValue(1);
    setVisible(m_visible);
}

QRectF BaseCursorItem::boundingRect() const
{
    if(Qt::Horizontal == m_cursorOrientation) {
        return QRectF(0, 0, m_size.width(), BaseCursorItem::s_defaultTooltipWidth);
    } else {
        return QRectF(0, 0, BaseCursorItem::s_defaultTooltipWidth, m_size.height());
    }
}

void BaseCursorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    paint_cursor(painter);
}

void BaseCursorItem::set_cursor_info(const S_CURSOR_INFO &cursorInfo)
{
    if(m_movingFlag) {
        return;
    }

    m_cursorInfo = cursorInfo;

    double lenght;
    if(Qt::Vertical == m_cursorOrientation) {
        lenght =  m_size.width();
    } else {
        lenght = m_size.height();
    }

    double pos =  (cursorInfo.currentValue - cursorInfo.start)
                    * (lenght / (cursorInfo.end - cursorInfo.start));

    pos -= (lenght / 2.0);
    m_cursorInfo.pos = pos;

    QPointF pointF = this->pos();
    if(m_cursorOrientation == Qt::Vertical) {
        pointF.setY(-m_size.height() / 2.0);    /* 限制指定移动路线 */
        pointF.setX(m_cursorInfo.pos);
    } else {
        pointF.setX(-m_size.width() / 2.0);     /* 限制指定移动路线 */
        pointF.setY(m_cursorInfo.pos);
    }

    setPos(pointF);
    update();
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

        double x = qMin(rect.right(), qMax(newPos.x(), rect.left()));
        double y = qMin(rect.bottom(), qMax(newPos.y(), rect.top()));

        if(!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(x);
            newPos.setY(y);
        }

        if(m_cursorOrientation == Qt::Vertical) {
            newPos.setY(-m_size.height() / 2.0);
            double lenght = m_size.width();
            m_cursorInfo.pos = x;
            double tmpX;
            if(x < 0.0) {
                tmpX = lenght / 2.0 - fabs(x);
            } else {
                tmpX = lenght / 2.0 + x;
            }

            m_cursorInfo.currentValue = tmpX * ((m_cursorInfo.end - m_cursorInfo.start) / lenght) + m_cursorInfo.start;

        } else {

            newPos.setX(-m_size.width() / 2.0);
            double lenght = m_size.height();
            m_cursorInfo.pos = y;
            double tmpY;
            if(y < 0.0) {
                tmpY = lenght / 2.0 - fabs(y);
            } else {
                tmpY = lenght / 2.0 + y;
            }
            m_cursorInfo.currentValue = tmpY * ((m_cursorInfo.end - m_cursorInfo.start) / lenght) + m_cursorInfo.start;
        }

        emit value_changed(m_cursorInfo.currentValue);

        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}


void BaseCursorItem::get_value(QString &valueText)
{
    valueText = QString::number(m_cursorInfo.currentValue, 'f', 2);
}


