#include "base_scan_scene.h"

#include <QDebug>
#include <QPainter>

#include <source/scan.h>

BaseScanScene::BaseScanScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent)
    : QGraphicsScene(parent),
      m_size(width(), height()),
      m_image(NULL),
      m_palette(palette),
      m_scrolling(false),
      m_redrawFlag(false),
      m_driving(DplSource::Scan::instance()->scan_axis()->driving()),
      m_pixPerBeamRatio(DEFAULT_PIX_PER_BEAM),
      m_beamsShowedCount(0.0),
      m_group(grp)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()), Qt::QueuedConnection);
}

bool BaseScanScene::set_pix_per_beam(double ratio)
{
    QWriteLocker lock(&m_rwLock);

    if(ratio < 0.0) {
        return false;
    }

    m_pixPerBeamRatio = ratio;

    return true;
}

bool BaseScanScene::need_refresh(const DplSource::BeamsPointer &beams)
{
    /* 更改扫查方式后（时间/编码器），需要更新C扫 */
    if(m_driving != DplSource::Scan::instance()->scan_axis()->driving()) {
        return true;
    }

    return false;
}


bool BaseScanScene::redraw_beams(const DplSource::BeamsPointer &beams)
{
    QWriteLocker lock(&m_rwLock);

    if(m_beamsPointer.isNull()) {
        m_beamsPointer = beams;
    }

    return redraw_vertical_beam();
}


void BaseScanScene::set_beams(const DplSource::BeamsPointer &beams)
{
    QWriteLocker lock(&m_rwLock);

    if(m_image == NULL) {
        qDebug() << "[" << __FUNCTION__ << "]" << " image is NULL. warning!!!!!";
        m_image = new QImage(m_size, QImage::Format_Indexed8);
        m_image->setColorTable(m_palette->colors());
        m_image->fill(Qt::white);
    }

    m_beamsPointer = beams;

    draw_vertical_beam();

    emit image_changed();
}


void BaseScanScene::set_size(const QSize &size)
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

    qDebug() << "[" << __FUNCTION__ << "]" << " w = " << size.width() << " h " << size.height();

    m_image = new QImage(m_size, QImage::Format_Indexed8);
    m_image->setColorTable(m_palette->colors());
    m_image->fill(Qt::white);

    setSceneRect(-size.width()/2, -size.height()/2,
                 size.width(), size.height());

    /* 根据最新的size以及当前显示的beam数，
     * 重新计算是否scroll */
    if(m_size.width() != 0
            && m_size.height() != 0
            && (!m_beamsPointer.isNull())) {

        check_scroll_window(size);
        m_redrawFlag = true;
    }

    qDebug() << "[" << __FUNCTION__ << "]" << " m_redrawFlag = " << m_redrawFlag;
}


void BaseScanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QWriteLocker lock(&m_rwLock);
    if(m_image != NULL) {
        painter->drawImage(rect, *m_image);
    }
}


void BaseScanScene::calculate_common_properties(BaseScanScene::S_CommonProperties &commonProperties)
{
    commonProperties.ratio      = m_beamsPointer->point_qty() / (double)m_image->height(); /* 一个像素点代表多少个point */
    commonProperties.pixCount   = m_pixPerBeamRatio;
    commonProperties.maxIndex   = m_image->width() / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */
    commonProperties.align      = m_image->width() % (int)(m_pixPerBeamRatio + 0.5);

    if(commonProperties.align != 0) {
         commonProperties.maxIndex += 1;
    }
}


void BaseScanScene::check_scroll_window(const QSize &oldSize)
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
    } else {
        m_scrolling = false;
    }
}

