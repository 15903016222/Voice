#include "s_scan_scene.h"

#include "s_scan_image.h"

#include <QPainter>

#include <device/device.h>

SscanScene::SscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent) :
    QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()), Qt::QueuedConnection);
}

SscanScene::~SscanScene()
{
    QWriteLocker l(&m_rwLock);
    if(m_image) {
        delete m_image;
        m_image = NULL;
    }
}

void SscanScene::set_size(const QSize &size)
{
    QWriteLocker l(&m_rwLock);

    setSceneRect(-size.width()/2, -size.height()/2,
                 size.width(), size.height());
    if (m_image) {
        delete m_image;
        m_image = NULL;
    }
    m_image = new SscanImage(DplDevice::Device::instance()->current_group(), size);
    m_image->setColorTable(m_palette->colors());
}

void SscanScene::set_beams(const DplSource::BeamsPointer &beams)
{
    QWriteLocker l(&m_rwLock);
    if (m_image) {
        m_image->draw_beams(beams);
        emit image_changed();
    }
}

void SscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QReadLocker l(&m_rwLock);

    if (m_image) {
        painter->drawImage(rect, *m_image);
    }
}
