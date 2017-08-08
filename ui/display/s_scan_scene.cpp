#include "s_scan_scene.h"
#include <QPainter>
#include <device/device.h>

SscanScene::SscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent) :
    QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette)
{

}

void SscanScene::set_size(const QSize &size)
{
    setSceneRect(-size.width()/2, -size.height()/2,
                 size.width(), size.height());
    if (m_image) {
        delete m_image;
        m_image = NULL;
    }
    m_image = new QImage(size, QImage::Format_Indexed8);
    m_image->setColorTable(m_palette->colors());
}

void SscanScene::draw_area(int x, int y, int w, int h, quint8 val)
{
    quint8 *image = (quint8 *)m_image->bits();
    for (int i=0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            image[m_image->width()*(j+y) + i+x] = val;
        }
    }
}

void SscanScene::show_beams(const DplSource::BeamsPointer &beams)
{
    int beamQty = beams->beam_qty();
    int pointQty = beams->point_qty();

    float xStep = m_image->width() * 1.0 / beamQty;
    float yStep = m_image->height() * 1.0 / pointQty;

    QByteArray beam;

    for (int i = 0; i < beamQty; ++i) {
        beam = beams->get(i)->get_wave();
        for (int j=0; j < pointQty; ++j) {
            draw_area(i*xStep, j*yStep, xStep, yStep+0.5,
                      (quint8)beam.at(j));
        }
    }

    update();
}

void SscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (m_image) {
        painter->drawImage(rect, *m_image);
    }
}
