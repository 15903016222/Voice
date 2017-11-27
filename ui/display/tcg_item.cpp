#include "tcg_item.h"
#include <QPainter>

TcgItem::TcgItem(const DplSizing::TcgsPointer &tcgs, const DplUt::SamplePointer &sample, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_tcgs(tcgs),
    m_sample(sample),
    m_size(400, 200)
{
}

QRectF TcgItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}

QPainterPath TcgItem::draw(const QByteArray &wave, bool rf, int w, int h)
{
    QPainterPath path;

    double xRatio = static_cast<double>(w) / ( wave.size() - 1);     // n个点，分为n-1段
    double yRatio = h / 255.0;

    int drawPoints = wave.size();

    if (rf) {
        for (int i = 0; i < drawPoints; ++i) {
            path.lineTo( i*xRatio,
                         ((uint)(128-(qint8)(wave.at(i)))) * yRatio);

        }
    } else {
        for (int i = 0; i < drawPoints; ++i) {
            path.lineTo( i*xRatio,
                         ((quint8)(255-wave.at(i))) * yRatio);
        }
    }

    return path;
}

void TcgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->translate(boundingRect().topLeft());
//    painter->setPen(m_ascan->color());
    painter->drawPath(m_path);

    float ratio = m_size.width() / m_sample->range();

//    DplSizing::TcgPointer tcg = m_tcgs->current_tcg();
//    int pointQty = m_tcgs->point_count();
//    /* draw points */
//    for (int i = 0; i < pointQty; ++i) {
//        int x = tcg->position(i) * ratio;
//        int y =
//    }
//    m_path.addRect();

    /* draw lines */
}

void TcgItem::set_wave(const QByteArray &beam, bool rf)
{
    if (!beam.isEmpty()) {
        m_path = draw(beam, rf, boundingRect().width(), boundingRect().height());
        emit painter_path_changed();
    }
}

void TcgItem::update()
{
    QGraphicsObject::update();
}
