#include "b_scan_scene.h"
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QWriteLocker>

#include <device/device.h>
#include <source/scan.h>
#include "Tracer.h"

BscanScene::BscanScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent) : QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette),
    m_size(QSize(width(), height())),
    m_pixPerBeamRatio(DEFAULT_PIX_PER_BEAM),
    m_group(group),
    m_redrawFlag(false),
    m_scrolling(false),
    m_beamsShowedCount(0)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()), Qt::QueuedConnection);
}

BscanScene::~BscanScene()
{
    QWriteLocker locker(&m_rwLock);

    if(NULL != m_image) {
        delete m_image;
        m_image = NULL;
    }
}


void BscanScene::set_size(const QSize &size)
{
    DEBUG_INIT("BscanScene", __FUNCTION__);

    qDebug() << "[" << __FUNCTION__ << "]" << " wait locker.";
    QWriteLocker lock(&m_rwLock);
    qDebug() << "[" << __FUNCTION__ << "]" << " no locker.";

    if((size.height() == m_size.height())
            && (size.width() == m_size.width())
            && (m_image != NULL))  {
        return;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " old m_size w = " << m_size.width()
             << " h = " << m_size.height();


    m_size = size;

    if(m_image != NULL) {
        delete m_image;
        m_image = NULL;
    }

    m_image = new QImage(m_size, QImage::Format_Indexed8);
    m_image->setColorTable(m_palette->colors());
    m_image->fill(Qt::white);

    setSceneRect(-size.width()/2,
                 -size.height()/2 + 1,
                 size.width(),
                 size.height());

    /* 根据最新的size以及当前显示的beam数，
     * 重新计算是否scroll */

    qDebug() << "[" << __FUNCTION__ << "]"
             << " new m_image w = " << m_image->width()
             << " h = " << m_image->height()
             << " m_size w = " << m_size.width()
             << " h = " << m_size.height();

    if(m_size.width() != 0
            && m_size.height() != 0
            && (!m_beamsPointer.isNull())) {

        check_scroll_window(size);

//        redraw_vertical_beam();
        m_redrawFlag = true;
    }
}


void BscanScene::set_beams(const DplSource::BeamsPointer &beamPointer)
{
    DEBUG_INIT("BscanScene", __FUNCTION__);

    QWriteLocker lock(&m_rwLock);

    if(m_image == NULL) {

        qDebug() << "[" << __FUNCTION__ << "]" << "m_image is NULL.";
        return;
    }

    m_beamsPointer = beamPointer;

    draw_vertical_beam();

    qDebug() << "[" << __FUNCTION__ << "]" << "send image_changed signal.";
    emit image_changed();

}


void BscanScene::reset()
{
    QWriteLocker lock(&m_rwLock);

    if(NULL != m_image) {

        m_image->setColorTable(m_palette->colors());
        m_image->fill(Qt::white);
        m_beamsShowedCount = 0;
        m_scrolling = false;
    }
}

bool BscanScene::set_pix_per_beam(double ratio)
{
    QWriteLocker lock(&m_rwLock);

    if(ratio < 0.0) {
        return false;
    }

    m_pixPerBeamRatio = ratio;

    return true;
}

bool BscanScene::set_current_beam(unsigned int index)
{
    QWriteLocker lock(&m_rwLock);
    m_currentIndex = index;
}

bool BscanScene::redraw_beams()
{
    QWriteLocker lock(&m_rwLock);

    if(!m_redrawFlag) {
        return false;
    }

    redraw_vertical_beam();
    m_redrawFlag = false;
    return true;
}

bool BscanScene::need_refresh()
{
    if(m_driving != DplSource::Scan::instance()->scan_axis()->driving()) {
        return true;
    }

    return false;
}


void BscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QWriteLocker lock(&m_rwLock);
    DEBUG_INIT("BscanScene", __FUNCTION__);
    if(m_image != NULL) {
        painter->drawImage(rect, *m_image);
    }
}



void BscanScene::calculate_common_properties(BscanScene::S_CommonProperties &commonProperties)
{
    commonProperties.ratio      = m_beamsPointer->point_qty() / (double)m_image->height(); /* 一个像素点代表多少个point */
    commonProperties.pixCount   = m_pixPerBeamRatio;
    commonProperties.maxIndex   = m_image->width() / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */
    commonProperties.align      = m_image->width() % (int)(m_pixPerBeamRatio + 0.5);

    if(commonProperties.align != 0) {
         commonProperties.maxIndex += 1;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " ratio = " << commonProperties.ratio
             << " pixCount = " << commonProperties.pixCount
             << " maxIndex = " << commonProperties.maxIndex
             << " align = " << commonProperties.align
             << " m_pixPerBeamRatio = " << m_pixPerBeamRatio;
}

void BscanScene::calculate_redraw_properties(BscanScene::S_CommonProperties &commonProperties,
                                             BscanScene::S_RedrawProperties &redrawProperites)
{
    DEBUG_INIT("BscanTimeScene", __FUNCTION__);
    /* index从0开始 */
    redrawProperites.currentFrameIndex  = m_beamsPointer->get(0)->index() / DplDevice::Device::instance()->beam_qty();
    redrawProperites.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();

    if(m_scrolling) {
        /* 滚动显示 */
        redrawProperites.redrawCount = commonProperties.maxIndex;
    } else {
        /* 未滚动显示 */
        redrawProperites.redrawCount = m_beamsShowedCount;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " maxIndex = " << commonProperties.maxIndex
             << " redrawCount = " << redrawProperites.redrawCount
             << " m_beamsShowedCount = " << m_beamsShowedCount
             << " scrolling = " << m_scrolling
             << " h target = " << m_image->height() / m_pixPerBeamRatio
             << " w target = " << m_image->width() / m_pixPerBeamRatio;


    redrawProperites.beginShowIndex = redrawProperites.currentFrameIndex - redrawProperites.redrawCount + 1;

    qDebug() << "[" << __FUNCTION__ << "]"
             << " currentFrameIndex = " << redrawProperites.currentFrameIndex
             << " beginShowIndex = " << redrawProperites.beginShowIndex
             << " redrawCount = " << redrawProperites.redrawCount
             << " totalFrameCount = " << redrawProperites.totalFrameCount;
}


void BscanScene::set_vertical_image_data(int beamsShowedCount,
                                const BscanScene::S_CommonProperties &commonProperties,
                                const quint8 *waveData)
{
    DEBUG_INIT("BscanTimeScene", __FUNCTION__);

    qDebug() << "[" << __FUNCTION__ << "]"
             << " m_image w = " << m_image->width()
             << " h = " << m_image->height()
             << " m_size w = " << m_size.width()
             << " h = " << m_size.height();

    if((beamsShowedCount + 1) == commonProperties.maxIndex && (commonProperties.align != 0)) {
        /* 非对齐,最后一条beam */
        int offset =  commonProperties.pixCount - commonProperties.align;
        QImage tmp = m_image->copy(offset, 0, m_image->width(), m_image->height());
        m_image->swap(tmp);

        int pos = 0;
        for(int i = 0; i < m_image->height(); ++i) {

            quint8 *line    = (quint8*) m_image->scanLine(i);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                pos = m_image->width() - j - 1;
                if(pos >= m_image->width() || pos < 0) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " last beam error pos = " << pos;
                    continue;
                }

                line[pos] = waveData[(int)(i * commonProperties.ratio)];
            }
        }

    } else {

        int pos = 0;
        for(int lineNum = 0; lineNum < m_image->height(); ++lineNum) {

            quint8 *line    = (quint8*) m_image->scanLine(lineNum);

            for(int j = 0; j < commonProperties.pixCount; ++j) {

                pos = (int)(beamsShowedCount * commonProperties.pixCount + j);

                if(pos >= m_image->width() || pos < 0) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " error pos = " << pos
                             << " pixCount = " << commonProperties.pixCount
                             << " j = " << j
                             << " lineNum = " << lineNum
                             << " beamsShowedCount = " << beamsShowedCount;
                    continue;
                }

                line[pos] = waveData[(int)(lineNum * commonProperties.ratio)];
            }
        }
    }
}



void BscanScene::scroll_vertical_image(const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
{
    DEBUG_INIT("BscanTimeScene", __FUNCTION__);

    QImage tmp = m_image->copy(commonProperties.pixCount, 0, m_image->width(), m_image->height());
    m_image->swap(tmp);
    int pos = 0;
    for(int i = 0; i < m_image->height(); ++i) {
        quint8 *line = (quint8*) m_image->scanLine(i);
        for(int j = 0; j < commonProperties.pixCount; ++j) {

            pos = m_image->width() - j - 1;

            if(pos >= m_image->width() || pos < 0) {
                qDebug() << "[" << __FUNCTION__ << "]" << " error pos = " << pos;
                continue;
            }

            line[pos] = waveData[(int)(i * commonProperties.ratio)];
        }
    }
}


void BscanScene::check_scroll_window(const QSize &oldSize)
{
    int newWidth = m_size.width();
    int oldWidth = oldSize.width();

    int newMaxIndex   = newWidth / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */

    /* size变小,同时已显示数超过最新size的最大显示数 */
    /* size变大，同时当前已为滚动状态 */

    if((oldWidth >= newWidth && m_beamsShowedCount > newMaxIndex)
            || (oldWidth <= newWidth && m_scrolling && m_beamsShowedCount > newMaxIndex)) {
        /* 滚动 */
        m_scrolling = true;
    }
}

void BscanScene::redraw_vertical_beam()
{

}


void BscanScene::draw_vertical_beam()
{

}





