#include "b_wave_item.h"
#include <QPainter>
#include <QDebug>
#include <QImage>
#include <QPaintDevice>
#include "color_bar.h"


BWaveItem::BWaveItem(ColorBar *colorBar, QGraphicsWidget *parent) :
    QGraphicsWidget(parent),
    m_size(380, 405),
    m_colorBar(colorBar),
    m_image(NULL)
{

}


QRectF BWaveItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}


void BWaveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(m_image == NULL || m_beams.isNull()) {
        qDebug("[%s]", __FUNCTION__);
        return;
    }

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = m_size.height() / 255.0;

    int drawPoints = 0;

    if (m_beams->get(0)->get_wave().size() < m_size.width()) {
        /* 当beam的点数小于寬度 */
        xRatio1 = m_size.width() / 1.0 / m_beams->get(0)->get_wave().size(); /* beam的每个point代表多少个像素 */
        drawPoints = m_beams->get(0)->get_wave().size();
    } else {
        /* 当beam的点数大于寬度 */
        xRatio2 = m_beams->get(0)->get_wave().size() / 1.0 / m_size.width(); /* 一个像素点代表多少个point */
        drawPoints = m_size.width();
    }

    /* 画最少的点 */
    for (int i = 0; i < drawPoints; ++i) {

       // QColorPointer colorPointer = m_colorBar->color(((quint8)(255 - (m_beams->get(0)->get_wave().at((int)(i * xRatio2)))) * yRatio - 0.5));

       // m_image->setPixel(i, m_beams->get(0)->index() % m_size.height(), colorPointer->rgba());
   }

    painter->drawImage(QPointF(-m_size.width() / 2, -m_size.height() / 2), *m_image);

}

void BWaveItem::set_size(const QSize &size)
{
    if((size.height() == m_size.height())
            && (size.width() == m_size.width())
            && (m_image != NULL))  {
        return;
    }

    m_size = size;

    if(m_image == NULL) {
        m_image = new QImage(size, QImage::Format_RGB32);
    } else {
        delete m_image;
        m_image = new QImage(size, QImage::Format_RGB32);
    }

    update();
}

void BWaveItem::set_wave(const DplSource::BeamsPointer &beams)
{
    m_beams = beams;
    update();
}
