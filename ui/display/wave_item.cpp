#include "wave_item.h"
#include <QPainter>

WaveItem::WaveItem(const DplDisplay::AscanPointer &ascan, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_ascan(ascan),
    m_size(400, 200)
{

}

QRectF WaveItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}

QPainterPath WaveItem::draw(const QByteArray &wave, int w, int h)
{
    QPainterPath path;

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = h / 255.0;

    int drawPoints = 0;
    if ( wave.size() < w) {
        xRatio1 = w / 1.0 / wave.size();
        drawPoints = wave.size();
    } else {
        xRatio2 = wave.size() / 1.0 / w;
        drawPoints = w;
    }

    for (int i = 0; i < drawPoints; ++i) {
        path.lineTo( i*xRatio1,
                     ((quint8)(255-wave.at((int)(i*xRatio2)))) * yRatio - 0.5);
    }

    return path;
}

void WaveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->translate(boundingRect().topLeft());
    painter->setPen(m_ascan->color());
    painter->drawPath(draw(m_beam,
                           boundingRect().width(),
                           boundingRect().height()));
}
