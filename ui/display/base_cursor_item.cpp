#include "base_cursor_item.h"

#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QString>

#include <measure/cursor.h>


static const int    DEFAULT_TOOLTIP_WIDTH  = 25;
static const int    DEFAULT_TOOLTIP_HEIGHT = 13;

BaseCursorItem::BaseCursorItem(Qt::Orientation cursorOrientation,
                               const DplDevice::GroupPointer &group,
                               E_CURSOR_TYPE cursorType,
                               E_CURSOR_SOURCE_TYPE sourceType,
                               QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_cursorOrientation(cursorOrientation),
    m_group(group),
    m_sourceType(sourceType),
    m_movingFlag(false),
    m_visible(false)
{
    if(cursorType == BaseCursorItem::REFERENCE) {
        m_color = QColor(Qt::blue);
    } else {
        m_color = QColor(Qt::red);
    }

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setVisible(m_visible);

    init_update_pos();

    connect(Mcu::instance(), SIGNAL(key_event(Mcu::KeyType)),
            this, SLOT(do_mcu_key_event(Mcu::KeyType)),
            Qt::DirectConnection);

    connect(this, SIGNAL(visible_changed(bool)), this, SLOT(do_visible_changed(bool)));
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

    paint_cursor(painter);
}

void BaseCursorItem::do_visible_changed(bool flag)
{
    setVisible(flag);
}

void BaseCursorItem::update_pos(float value)
{
    /* 参考值/测量值 更新pos */
}

void BaseCursorItem::do_mcu_key_event(Mcu::KeyType type)
{
    if (type != Mcu::KEY_CURSOR) {
        return;
    }

    if (DplDevice::Device::instance()->is_running()) {
        return;
    }

    if(m_visible) {
        m_visible = false;
    } else {
        m_visible = true;
    }

    emit visible_changed(m_visible);
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
        }

        if(m_cursorOrientation == Qt::Vertical) {
            newPos.setY(0.0);
        } else {
            newPos.setX(0.0);
        }

        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}


void BaseCursorItem::get_value(QString &valueText)
{
    valueText.append(tr("11.88"));
}

void BaseCursorItem::init_update_pos()
{
    if(BaseCursorItem::Amplitude == m_sourceType) {

    } else if(BaseCursorItem::Scan == m_sourceType) {

    } else if(BaseCursorItem::Index == m_sourceType) {

    } else if(BaseCursorItem::Ultrasound == m_sourceType) {

    }
}


VScanCursorItem::VScanCursorItem(Qt::Orientation cursorOrientation,
                                 const DplDevice::GroupPointer &group,
                                 BaseCursorItem::E_CURSOR_TYPE cursorType,
                                 BaseCursorItem::E_CURSOR_SOURCE_TYPE sourceType,
                                 QGraphicsItem *parent) :
    BaseCursorItem(cursorOrientation, group, cursorType, sourceType, parent)
{

}

void VScanCursorItem::paint_cursor(QPainter *painter)
{
    /* 指示框 */
    QColor color(205, 205, 205); /* 灰色 */

    QRectF rectF;
    QFont font;
    font.setPointSize(8);
    rectF = QRectF(-m_size.width() / 2.0,
                -m_size.height() / 2.0,
                DEFAULT_TOOLTIP_WIDTH,
                DEFAULT_TOOLTIP_HEIGHT);

    painter->fillRect(rectF, QBrush(color));
    painter->setPen(QColor(Qt::black));
    painter->setFont(font);
    QString valueText;
    get_value(valueText);
    painter->drawText(rectF, valueText, QTextOption(Qt::AlignCenter));

    painter->setPen(m_color);
    QPointF startPoint(-m_size.width() / 2.0,
                   -m_size.height() / 2.0);

    if(Qt::Vertical == m_cursorOrientation) {

        QPointF endPoint(-m_size.width() / 2.0,
                       m_size.height());
        painter->drawLine(startPoint, endPoint);

    } else {

        QPointF endPoint(m_size.width() / 2.0,
                       -m_size.height() / 2.0);
        painter->drawLine(startPoint, endPoint);

    }
}

HScanCursorItem::HScanCursorItem(Qt::Orientation cursorOrientation,
                                 const DplDevice::GroupPointer &group,
                                 BaseCursorItem::E_CURSOR_TYPE cursorType,
                                 BaseCursorItem::E_CURSOR_SOURCE_TYPE sourceType,
                                 QGraphicsItem *parent) :
    BaseCursorItem(cursorOrientation, group, cursorType, sourceType, parent)
{

}

void HScanCursorItem::paint_cursor(QPainter *painter)
{
    /* 指示框 */
    QColor color(205, 205, 205); /* 灰色 */

    QRectF rectF;
    QFont font;
    font.setPointSize(8);

    if(Qt::Horizontal == m_cursorOrientation) {

        rectF = QRectF(m_size.width() / 2.0 - DEFAULT_TOOLTIP_HEIGHT,
                     -m_size.height() / 2.0,
                     DEFAULT_TOOLTIP_HEIGHT,
                     DEFAULT_TOOLTIP_WIDTH);

        painter->fillRect(rectF, QBrush(color));
        painter->setPen(QColor(Qt::black));
        painter->setFont(font);
        /* 旋转90度 */
        painter->rotate(90);
        QString valueText;
        get_value(valueText);
        painter->drawText(QRectF(-m_size.height() / 2.0,
                                 -m_size.width() / 2.0,
                                 DEFAULT_TOOLTIP_WIDTH,
                                 DEFAULT_TOOLTIP_HEIGHT),
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
                     DEFAULT_TOOLTIP_HEIGHT,
                     DEFAULT_TOOLTIP_WIDTH);

        painter->fillRect(rectF, QBrush(color));
        painter->setPen(QColor(Qt::black));
        painter->setFont(font);
        /* 旋转90度 */
        painter->rotate(90);

        QString valueText;
        get_value(valueText);
        painter->drawText(QRectF(-m_size.height() / 2.0,
                                 m_size.width() / 2.0 - DEFAULT_TOOLTIP_HEIGHT,
                                 DEFAULT_TOOLTIP_WIDTH,
                                 DEFAULT_TOOLTIP_HEIGHT),
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
