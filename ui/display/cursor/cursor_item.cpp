#include "cursor_item.h"

#include "../base/scan_view.h"
#include <QGraphicsScene>
#include <QPainter>

static const int DEFAULT_WIDTH = 40;
static const int DEFAULT_TEXT_HEIGHT = 13;
static const int DEFAULT_TEXT_WIDTH = 34;

CursorItem::CursorItem(const DplMeasure::CursorPointer &cursor,
                       Qt::Orientation cursorOrientation,
                       QColor color, QColor bgColor) :
    QGraphicsObject(),
    m_cursor(cursor),
    m_orientation(cursorOrientation),
    m_color(color),
    m_bgColor(bgColor),
    m_movingFlag(false),
    m_direction(NORMAL)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setZValue(1);

    connect(this, SIGNAL(xChanged()),
            this, SLOT(position_event()));
    connect(this, SIGNAL(yChanged()),
            this, SLOT(position_event()));
    connect(this, SIGNAL(size_changed()),
            this, SLOT(update_position()));

    connect(static_cast<DplMeasure::Cursor *>(cursor.data()),
            SIGNAL(visible_changed(bool)),
            this, SLOT(setVisible(bool)));
    setVisible(cursor->is_visible());
}

QRectF CursorItem::boundingRect() const
{
    if(Qt::Horizontal == m_orientation) {
        return QRectF(0, -DEFAULT_WIDTH/2,
                      m_size.width(), DEFAULT_WIDTH);
    } else {
        return QRectF(-DEFAULT_WIDTH/2, 0,
                      DEFAULT_WIDTH, m_size.height());
    }
}

void CursorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(m_color);
    painter->setFont(QFont("Arial", 8, QFont::Normal));

    if (Qt::Horizontal == m_orientation) {
        painter->drawLine(0, 0, m_size.width(), 0);

    } else {
        painter->drawLine(0, 0, 0, m_size.height());
    }

    Qt::Orientation viewOrientation = Qt::Horizontal;
    if (scene() && !scene()->views().isEmpty()) {
        ScanView *view = static_cast<ScanView *>(scene()->views().at(0));
        viewOrientation = view->orientation();
    }

    painter->setPen(Qt::black);

    if (m_orientation == Qt::Horizontal) {
        if (viewOrientation == Qt::Vertical) {
            painter->rotate(-90);
            painter->translate(0, DEFAULT_TEXT_HEIGHT);
        }
        if (m_direction == NORMAL) {
            painter->fillRect(0, -DEFAULT_TEXT_HEIGHT,
                              DEFAULT_TEXT_WIDTH, DEFAULT_TEXT_HEIGHT,
                              m_bgColor);
            painter->drawText(0, -DEFAULT_TEXT_HEIGHT,
                              DEFAULT_TEXT_WIDTH, DEFAULT_TEXT_HEIGHT,
                              Qt::AlignCenter,
                              m_text);
        } else {
            painter->fillRect(m_size.width()-DEFAULT_TEXT_WIDTH, 0,
                              DEFAULT_TEXT_WIDTH, DEFAULT_TEXT_HEIGHT,
                              m_bgColor);
            painter->drawText(m_size.width()-DEFAULT_TEXT_WIDTH, 0,
                              DEFAULT_TEXT_WIDTH, DEFAULT_TEXT_HEIGHT,
                              Qt::AlignCenter,
                              m_text);
        }
    } else {
        if (viewOrientation == Qt::Vertical) {
            painter->rotate(-90);
            painter->translate(-DEFAULT_TEXT_WIDTH, 0);
        }
        painter->fillRect(0, 0, DEFAULT_TEXT_WIDTH, DEFAULT_TEXT_HEIGHT,
                          m_bgColor);
        painter->drawText(0, 0,
                          DEFAULT_TEXT_WIDTH, DEFAULT_TEXT_HEIGHT,
                          Qt::AlignCenter,
                          m_text);
    }
}

void CursorItem::setVisible(bool flag)
{
    QGraphicsObject::setVisible(flag);
}

void CursorItem::update_position()
{
    if (moving()) {
        return;
    }

    if (orientation() == Qt::Horizontal) {
        if (m_direction == NORMAL) {
            setPos(0, m_size.height() - m_size.height() * ratio());
        } else {
            setPos(0, m_size.height() * ratio());
        }
    } else {
        if (m_direction == NORMAL) {
            setPos(m_size.width() * ratio(), 0);
        } else {
            setPos(m_size.width() - m_size.width() * ratio(), 0);
        }
    }
}

void CursorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = true;
    QGraphicsItem::mousePressEvent(event);
}

void CursorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant CursorItem::itemChange(QGraphicsItem::GraphicsItemChange change,
                                const QVariant &value)
{
    if (change == ItemPositionChange && moving()) {
        QPointF newPos = value.toPointF();

        if (Qt::Horizontal == m_orientation) {
            newPos.setX(0);
        } else {
            newPos.setY(0);
        }

        if (newPos.x() < 0) {
            newPos.setX(0);
        } else if (newPos.x() > m_size.width()) {
            newPos.setX(m_size.width());
        }

        if (newPos.y() < 0) {
            newPos.setY(0);
        } else if (newPos.y() > m_size.height()) {
            newPos.setY(m_size.height());
        }

        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}
