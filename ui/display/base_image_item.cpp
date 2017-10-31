#include "base_image_item.h"

#include <QDebug>
#include <QPainter>

#include <source/scan.h>
#include <typeinfo>

BaseImageItem::BaseImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QGraphicsObject *parent)
    : QGraphicsObject(parent),
      m_image(NULL),
      m_scrolling(false),
      m_redrawFlag(false),
      m_driving(DplSource::Scan::instance()->scan_axis()->driving()),
      m_palette(palette),
      m_pixPerBeamRatio(DEFAULT_PIX_PER_BEAM),
      m_beamsShowedCount(0.0),
      m_group(grp),
      m_initFinished(false)
{
    connect(this, SIGNAL(image_changed()),
            this, SLOT(update()));
}

BaseImageItem::~BaseImageItem()
{
    QWriteLocker lock(&m_rwLock);

    if(m_image) {
        delete m_image;
        m_image = NULL;
    }
}

bool BaseImageItem::set_pix_per_beam(double ratio)
{
    QWriteLocker lock(&m_rwLock);

    if(ratio < 0.0) {
        return false;
    }

    m_pixPerBeamRatio = ratio;

    return true;
}

bool BaseImageItem::need_refresh(const DplSource::BeamsPointer &beams)
{
    Q_UNUSED(beams);

    /* 更改扫查方式后（时间/编码器），需要更新C扫 */
    if(m_driving != DplSource::Scan::instance()->scan_axis()->driving()) {
        return true;
    }

    return false;
}


bool BaseImageItem::redraw_beams(const DplSource::BeamsPointer &beams)
{
    qDebug("[%s:%s] debug here.", "BaseImageItem", __FUNCTION__);

    QWriteLocker lock(&m_rwLock);

    if(m_image == NULL) {
        return false;
    }

    if(m_beamsPointer.isNull()) {
        m_beamsPointer = beams;
    }

    return redraw_vertical_beam();
}


void BaseImageItem::set_beams(const DplSource::BeamsPointer &beams)
{
    qDebug("[%s:%s] debug here.", "BscanDisplay", __FUNCTION__);

    QWriteLocker lock(&m_rwLock);

    if(m_image == NULL) {
        qDebug() << "[" << __FUNCTION__ << "]" << " image is NULL. warning!!!!!";
        return;
    }

    if(!m_initFinished) {
        qDebug() << "[" << __FUNCTION__ << "]" << " had not been init finished.";
        return;
    }

    m_beamsPointer = beams;

    draw_vertical_beam();

    emit image_changed();
}


void BaseImageItem::set_size(const QSize &size)
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
    m_image->fill(Qt::white);

    /* 根据最新的size以及当前显示的beam数，
     * 重新计算是否scroll */
    if(m_size.width() != 0
            && m_size.height() != 0
            && (!m_beamsPointer.isNull())) {

        check_scroll_window(size);
        m_redrawFlag = true;
    }
}

void BaseImageItem::update()
{
    QGraphicsObject::update();
}


void BaseImageItem::calculate_common_properties(BaseImageItem::S_CommonProperties &commonProperties)
{
    commonProperties.ratio      = m_beamsPointer->point_qty() / (double)m_image->height(); /* 一个像素点代表多少个point */
    commonProperties.pixCount   = m_pixPerBeamRatio;
    commonProperties.maxIndex   = m_image->width() / (int)(m_pixPerBeamRatio + 0.5);  /* 最大的beam数 */
    commonProperties.align      = m_image->width() % (int)(m_pixPerBeamRatio + 0.5);

    if(commonProperties.align != 0) {
         commonProperties.maxIndex += 1;
    }
}


void BaseImageItem::check_scroll_window(const QSize &oldSize)
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


QRectF BaseImageItem::boundingRect() const
{
    return QRectF(-m_size.width()/2.0, -m_size.height()/2.0,
                  m_size.width(), m_size.height());
}

void BaseImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QWriteLocker lock(&m_rwLock);

    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(m_image) {
        painter->drawImage(boundingRect(), *m_image);
    }
}


