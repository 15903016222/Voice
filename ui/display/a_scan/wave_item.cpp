#include "wave_item.h"
#include <QPainter>

WaveItem::WaveItem(const DplDisplay::AscanPointer &ascan,
                   QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_ascan(ascan),
    m_size(400, 200)
{
    connect(this, SIGNAL(painter_path_changed()),
            this, SLOT(update()), Qt::QueuedConnection);
}

QRectF WaveItem::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

QPainterPath WaveItem::draw(const QByteArray &wave, bool rf)
{
    QPainterPath path;

    double xRatio = static_cast<double>(m_size.width()) / ( wave.size() - 1);//n个点，分为n-1段
    double yRatio = m_size.height() / 255.0;

    int drawPoints = wave.size();

    if (rf) {
        for (int i = 0; i < drawPoints; ++i) {
            path.lineTo( i*xRatio,
                         - (qAbs(wave.at(i)-128)) * yRatio);

        }
    } else {
        for (int i = 0; i < drawPoints; ++i) {
            path.lineTo( i*xRatio,
                         - static_cast<quint8>(wave.at(i)) * yRatio);
        }
    }

    return path;
}

void WaveItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{    
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QMutexLocker l(&m_mutex);

    painter->translate(0, m_size.height()-1);
    painter->setPen(m_ascan->color());
    painter->drawPath(m_path);
}

void WaveItem::set_wave(const QByteArray &beam, bool rf)
{
    QMutexLocker l(&m_mutex);
    if (!beam.isEmpty()) {
        m_path = draw(beam, rf);
        emit painter_path_changed();
    }
}

void WaveItem::update()
{
    QGraphicsObject::update();
}
