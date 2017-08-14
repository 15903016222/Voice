#include "s_scan_scene.h"

#include "s_scan_image.h"

#include <QPainter>
#include <QThread>

#include <device/device.h>

SscanScene::SscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent) :
    QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette),
    m_thread(new QThread(this))
{
    connect(m_thread, SIGNAL(started()),
            this, SLOT(show_beams()), Qt::DirectConnection);
    connect(m_thread, SIGNAL(finished()),
            this, SLOT(update()), Qt::DirectConnection);
}

void SscanScene::set_size(const QSize &size)
{
    setSceneRect(-size.width()/2, -size.height()/2,
                 size.width(), size.height());
    if (m_image) {
        delete m_image;
        m_image = NULL;
    }
    m_image = new SscanImage(size);
    m_image->setColorTable(m_palette->colors());
}

void SscanScene::show_beams(const DplSource::BeamsPointer &beams)
{
    m_image->draw_beams(beams);
    update();
}

void SscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (m_image) {
        painter->drawImage(rect, *m_image);
    }
}
