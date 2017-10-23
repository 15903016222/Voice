#include "base_cursor_item.h"
#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QDebug>

BaseCursorItem::BaseCursorItem(Qt::Orientation orientation, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_movingFlag(false),
    m_color(Qt::red),
    m_orientation(orientation)
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

    /* 指示框 */
    QColor color(205, 205, 205); /* 灰色 */

    QRectF rectF;
    QFont font;
    font.setPointSize(8);

    if(m_orientation == Qt::Vertical) {
         rectF = QRectF(-m_size.width() / 2.0,
                     -m_size.height() / 2.0,
                     DEFAULT_TOOLTIP_WIDTH,
                     DEFAULT_TOOLTIP_HEIGHT);

         painter->fillRect(rectF, QBrush(color));
         painter->setPen(QColor(Qt::black));
         painter->setFont(font);
         painter->drawText(rectF, QString::number(11.88),
                           QTextOption(Qt::AlignCenter));

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
                                 -m_size.width() / 2.0,
                                 DEFAULT_TOOLTIP_WIDTH,
                                 DEFAULT_TOOLTIP_HEIGHT),
                          QString::number(11.88),
                          QTextOption(Qt::AlignCenter));

        qDebug() << " x  = " << -m_size.height() / 2.0
                 <<  " y = " << -m_size.width() / 2.0;

        painter->rotate(-90);
    }

    painter->setBrush(QBrush(m_color));
    QPointF point1(-m_size.width() / 2.0,
                   -m_size.height() / 2.0);

    QPointF point2(-m_size.width() / 2.0,
                   m_size.height());

    painter->drawLine(point1, point2);
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
