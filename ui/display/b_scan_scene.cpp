#include "b_scan_scene.h"
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <QWriteLocker>

#include <device/device.h>

BscanScene::BscanScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent) : QGraphicsScene(parent),
    m_image(NULL),
    m_palette(palette),
    m_pixPerBeamRatio(1.0),
    m_beamsShowedCount(0),
    m_size(QSize(width(), height())),
    m_group(group),
    m_scrolling(false)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()));

}

BscanScene::~BscanScene()
{
    QWriteLocker locker(&m_rwLock);

    if(NULL != m_image) {
        delete m_image;
    }
}


void BscanScene::set_size(const QSize &size)
{
    QWriteLocker lock(&m_rwLock);

    if((size.height() == m_size.height())
            && (size.width() == m_size.width())
            && (m_image != NULL))  {
        return;
    }

    m_size = size;

    if(m_image != NULL) {
        delete m_image;
        m_image = NULL;
    }

    m_image = new QImage(m_size, QImage::Format_Indexed8);
    m_image->setColorTable(m_palette->colors());
    m_image->fill(Qt::red);

    /* 根据最新的size以及当前显示的beam数，
     * 重新计算是否scroll */

    if(m_size.width() != 0
            && m_size.height() != 0
            && (!m_beamsPointer.isNull())) {

        check_scroll_window(size);

        reset_show();
    }
}


void BscanScene::set_beams(const DplSource::BeamsPointer &beamPointer)
{
    QWriteLocker lock(&m_rwLock);

    m_beamsPointer = beamPointer;

    if(m_image == NULL) {

        qDebug() << "[" << __FUNCTION__ << "]" << "m_image is NULL.";
        return;
    }

    draw_beams();

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


void BscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QWriteLocker lock(&m_rwLock);

    if(m_image != NULL) {
        painter->drawImage(rect, *m_image);
    }
}


void BscanScene::draw_beams()
{
    draw_vertical_beam();
}


void BscanScene::reset_show()
{
   redraw_vertical_beam();
}

void BscanScene::calculate_common_properties(BscanScene::S_CommonProperties &commonProperties)
{
    int height;
    int width;

    height =  m_size.height();
    width  = m_size.width();

    commonProperties.ratio      = m_beamsPointer->point_qty() / (double)height; /* 一个像素点代表多少个point */
    commonProperties.pixCount   = m_pixPerBeamRatio;
    commonProperties.maxIndex   = width / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */
    commonProperties.align      = width % (int)(m_pixPerBeamRatio + 0.5);

    if(commonProperties.align != 0) {
         commonProperties.maxIndex += 1;
    }
}

void BscanScene::calculate_redraw_properties(BscanScene::S_CommonProperties &commonProperties,
                                             BscanScene::S_RedrawProperties &redrawProperites)
{
    /* index从0开始 */
    redrawProperites.currentFrameIndex  = m_beamsPointer->get(0)->index() / DplDevice::Device::instance()->total_beam_qty();
    redrawProperites.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();

    if(m_scrolling) {
        /* 滚动显示 */
        redrawProperites.redrawCount = commonProperties.maxIndex;
    } else {
        /* 未滚动显示 */
        redrawProperites.redrawCount = m_beamsShowedCount;
    }

    redrawProperites.beginShowIndex = redrawProperites.currentFrameIndex - redrawProperites.redrawCount + 1;
}


void BscanScene::set_vertical_image_data(int beamsShowedCount,
                                const BscanScene::S_CommonProperties &commonProperties,
                                const quint8 *waveData)
{
    if((beamsShowedCount + 1) == commonProperties.maxIndex && (commonProperties.align != 0)) {
        /* 非对齐,最后一条beam */
        int offset =  commonProperties.pixCount - commonProperties.align;
        QImage tmp = m_image->copy(offset, 0, m_image->width(), m_image->height());
        m_image->swap(tmp);

        for(int i = 0; i < m_size.height(); ++i) {

            quint8 *line    = (quint8*) m_image->scanLine(i);

            for(int j = 0; j < commonProperties.pixCount; ++j) {
                line[m_size.width() - j - 1] = waveData[(int)(i * commonProperties.ratio)];
            }
        }

    } else {

        for(int lineNum = 0; lineNum < m_size.height(); ++lineNum) {

            quint8 *line    = (quint8*) m_image->scanLine(lineNum);

            for(int j = 0; j < commonProperties.pixCount; ++j) {
                line[(int)(beamsShowedCount * commonProperties.pixCount + j)] = waveData[(int)(lineNum * commonProperties.ratio)];
            }
        }
    }
}


void BscanScene::set_horizontal_image_data(int beamsShowedCount, const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
{
    if((beamsShowedCount + 1) == commonProperties.maxIndex && (commonProperties.align != 0)) {
        /* 非对齐,最后一条beam */
        int offset =  commonProperties.pixCount - commonProperties.align;

        QImage tmp = m_image->copy(0, offset, m_image->width(), m_image->height());
        m_image->swap(tmp);

        for(int count = 0; count < commonProperties.pixCount; ++count) {
            quint8 *targetLine = (quint8*) m_image->scanLine(count);
            for(int j = 0; j < m_size.width(); ++j) {
                targetLine[j] = waveData[(int)(j * commonProperties.ratio)];
            }
        }

    } else {

        for (int count = 0; count < commonProperties.pixCount; ++count) {
            quint8 *line = (quint8*) m_image->scanLine(m_size.height() - beamsShowedCount * commonProperties.pixCount - count -1);
            for(int j = 0; j < m_size.width(); ++j) {
                line[j] = waveData[(int)(j * commonProperties.ratio)];
            }
        }
    }
}

void BscanScene::scroll_vertical_image(const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
{
    QImage tmp = m_image->copy(commonProperties.pixCount, 0, m_image->width(), m_image->height());
    m_image->swap(tmp);

    for(int i = 0; i < m_size.height(); ++i) {
        quint8 *line = (quint8*) m_image->scanLine(i);
        for(int j = 0; j < commonProperties.pixCount; ++j) {
            line[m_image->width() - j - 1] = waveData[(int)(i * commonProperties.ratio)];
        }
    }
}


void BscanScene::scroll_horizontal_image(const BscanScene::S_CommonProperties &commonProperties, const quint8 *waveData)
{
    QImage tmp = m_image->copy(0, commonProperties.pixCount, m_image->width(), m_image->height());
    m_image->swap(tmp);

    for(int i = 0; i < commonProperties.pixCount; ++i) {
        quint8 *targetLine = (quint8*) m_image->scanLine(i);
        for(int j = 0; j < m_size.width(); ++j) {
            targetLine[j] = waveData[(int)(j * commonProperties.ratio)];
        }
    }
}

void BscanScene::check_scroll_window(const QSize &oldSize)
{
    int newWidth = m_size.width();
    int oldWidth = oldSize.width();

    int newMaxIndex   = newWidth / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */

    /* size变小,同时已显示数超过最新size的最大显示数 */
    /* size变大，同时当前已为滚动状态且 */

    if((oldWidth >= newWidth && m_beamsShowedCount > newMaxIndex)
            || (oldWidth <= newWidth && m_scrolling && m_beamsShowedCount > newMaxIndex)) {
        /* 滚动 */
        m_scrolling = true;
    }
}


void BscanScene::redraw_horizontal_beam()
{           

}


void BscanScene::redraw_vertical_beam()
{

}

void BscanScene::draw_horizontal_beam()
{

}


void BscanScene::draw_vertical_beam()
{

}





