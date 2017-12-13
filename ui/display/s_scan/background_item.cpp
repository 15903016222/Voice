#include "background_item.h"

#include <QPainter>

BackgroundItem::BackgroundItem(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_size(400, 200)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()), Qt::QueuedConnection);
}

QRectF BackgroundItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}

void BackgroundItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(), m_pixmap, m_pixmap.rect());
}

void BackgroundItem::draw(const QImage &image)
{
    m_pixmap = QPixmap::fromImage(image);
    emit image_changed();
}

void BackgroundItem::update()
{
    QGraphicsObject::update();
}
