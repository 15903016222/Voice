#include "wave_item.h"
#include <QPainter>

WaveItem::WaveItem(const DplDisplay::AscanPointer &ascan, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_ascan(ascan),
    m_size(400, 200)
{
    connect(this, SIGNAL(painter_path_changed()),
            this, SLOT(update()), Qt::QueuedConnection);
}

QRectF WaveItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}

QPainterPath WaveItem::draw(const QByteArray &wave, bool rf, int w, int h)
{
    QPainterPath path;

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = h / 256.0;

    int drawPoints = 0;
    if ( wave.size() < w) {
        xRatio1 = w / 1.0 / wave.size();
        drawPoints = wave.size();
    } else {
        xRatio2 = wave.size() / 1.0 / w;
        drawPoints = w;
    }

    if (rf) {
        for (int i = 0; i < drawPoints; ++i) {
            qDebug("%s[%d](%d): y(%d) h(%d) yRatio(%f) val(%d)",__func__, __LINE__, i,
                   ((uint)(128-(qint8)(wave.at((int)(i*xRatio2))))),
                   h,
                   yRatio,
                   wave.at(i));
            path.lineTo( i*xRatio1,
                         ((uint)(128-(qint8)(wave.at((int)(i*xRatio2))))) * yRatio - 0.5 );

        }
    } else {
        for (int i = 0; i < drawPoints; ++i) {
            path.lineTo( i*xRatio1,
                         ((quint8)(255-wave.at((int)(i*xRatio2)))) * yRatio + 0.5);
        }
    }

    return path;
}

void WaveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QMutexLocker l(&m_mutex);

    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->translate(boundingRect().topLeft());
    painter->setPen(m_ascan->color());
    painter->drawPath(m_path);
}

void WaveItem::set_wave(const QByteArray &beam, bool rf)
{
    QMutexLocker l(&m_mutex);
    if (!beam.isEmpty()) {
        m_path = draw(beam, rf, boundingRect().width(), boundingRect().height());
        emit painter_path_changed();
    }
}

void WaveItem::update()
{
    QGraphicsObject::update();
}
