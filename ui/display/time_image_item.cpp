#include "time_image_item.h"

#include <source/source.h>

TimeImageItem::TimeImageItem(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QGraphicsObject *parent)
    : BaseImageItem(palette, grp, parent)
{

}


void TimeImageItem::draw_vertical_beam()
{
    qDebug("[%s:%s] debug here.", "TimeImageItem", __FUNCTION__);

    m_pendingTimeCount = TestStub::instance()->get_time();

    S_CommonProperties commonProperties;

    calculate_common_properties(commonProperties);

    /* 正在处理的第几帧 */
    int pendingFrameCount = (m_pendingTimeCount * SECOND) / DplSource::Source::instance()->interval();
    /* 系统一共有多少帧 */
    int totalFrameCount = STORE_BUFFER_SIZE / m_beamsPointer->size();

    DplSource::BeamsPointer beamsPointer = DplSource::Source::instance()->beams(m_group->index(),
                                                                                pendingFrameCount % totalFrameCount);
    if(m_scrolling) {
        /* 整个显示区域画满beam，开始滚动显示后续的beam */
        scroll_vertical_image(commonProperties, beamsPointer);
    } else {
        draw_vertical_image(m_beamsShowedCount, commonProperties, beamsPointer);
    }

    ++m_beamsShowedCount;
    m_currentTimeCount = m_pendingTimeCount;
}


bool TimeImageItem::redraw_vertical_beam()
{
    qDebug("[%s:%s] debug here.", "TimeImageItem", __FUNCTION__);

    QTime time;
    time.restart();

    if(m_beamsPointer.isNull() ) {
        return false;
    }

    m_pendingTimeCount = TestStub::instance()->get_time();
    double timeSpace = m_pendingTimeCount - m_currentTimeCount;
    int beamsCount = (timeSpace * SECOND) / DplSource::Source::instance()->interval();

    S_CommonProperties commonProperties;
    calculate_common_properties(commonProperties);

    S_RedrawProperties redrawProperties;

    if(beamsCount > commonProperties.maxIndex) {

        int pendingFrameCount = m_pendingTimeCount * SECOND / DplSource::Source::instance()->interval();

        redrawProperties.currentFrameIndex  = pendingFrameCount;
        redrawProperties.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();
        redrawProperties.redrawCount        = commonProperties.maxIndex;
        redrawProperties.beginShowIndex     = redrawProperties.currentFrameIndex - redrawProperties.redrawCount + 1;

    } else if(beamsCount > 1) {

        int pendingFrameCount = m_pendingTimeCount * SECOND / DplSource::Source::instance()->interval();
        int currentFrameCount = m_currentTimeCount * SECOND / DplSource::Source::instance()->interval();

        redrawProperties.currentFrameIndex  = pendingFrameCount;
        redrawProperties.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();
        redrawProperties.redrawCount        = pendingFrameCount - currentFrameCount;
        redrawProperties.beginShowIndex     = currentFrameCount;

    } else if(m_redrawFlag) {

        int pendingFrameCount = m_pendingTimeCount * SECOND / DplSource::Source::instance()->interval();

        int tmpRedrawCount = pendingFrameCount - commonProperties.maxIndex;
        if(tmpRedrawCount > 0) {
            redrawProperties.redrawCount    = commonProperties.maxIndex;
            redrawProperties.beginShowIndex = tmpRedrawCount;
        } else {
            redrawProperties.redrawCount    = pendingFrameCount;
            redrawProperties.beginShowIndex = 0;
        }

        redrawProperties.currentFrameIndex  = pendingFrameCount;
        redrawProperties.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();

    } else {
        /* no need to redraw */
        return false;
    }

    DplSource::BeamsPointer tmp;
    int tmpBeamsShowedCount = 0;

     /* 顺序显示beams */
    if(redrawProperties.beginShowIndex >= 0) {
        for(int i = 0; i < redrawProperties.redrawCount; ++i) {

            tmp = DplSource::Source::instance()->beams(m_group->index(),
                                                           (redrawProperties.beginShowIndex + i) % redrawProperties.totalFrameCount);
            if(tmp.isNull()) {
                qDebug() << "[" << __FUNCTION__ << "]" << " BeamsPointer is NULL. tmpBeamsShowedCount = " << tmpBeamsShowedCount;
            }

            draw_vertical_image(tmpBeamsShowedCount, commonProperties, tmp);

            ++tmpBeamsShowedCount;
        }
    } else {
        for(int i = 0; i < redrawProperties.redrawCount; ++i) {
            /*
             * ________________________________________________________
             * |__0__|__1__|____|____|____|.....  |__20__|__21__|__22__|
             * 以上为例子：
             * 当前帧为：1
             * 已显示帧数为：5
             * 则显示帧数顺序为：20、21、22、0、1
             */

            /* 从倒数第（totalFrameCount - lastIndex）个开始显示 */

            if(i < abs(redrawProperties.beginShowIndex)) {
                int index = redrawProperties.totalFrameCount + redrawProperties.beginShowIndex + i;
                tmp = DplSource::Source::instance()->beams(m_group->index(), index);
            } else {
                tmp = DplSource::Source::instance()->beams(m_group->index(), i - abs(redrawProperties.beginShowIndex));
            }

            if(tmp.isNull()) {
                qDebug() << "[" << __FUNCTION__ << "]" << " BeamsPointer is NULL. tmpBeamsShowedCount = " << tmpBeamsShowedCount;
            }

            draw_vertical_image(tmpBeamsShowedCount, commonProperties, tmp);

            ++tmpBeamsShowedCount;
        }
    }

    m_beamsShowedCount = tmpBeamsShowedCount;
    m_currentTimeCount = m_pendingTimeCount;
    m_redrawFlag       = false;

    qDebug("TimeImageItem:%s[%d]: Take Time: %d(ms)",__func__, __LINE__, time.elapsed());

    return true;
}


void TimeImageItem::draw_vertical_image(int beamsShowedCount,
                                        const BaseImageItem::S_CommonProperties &commonProperties,
                                        const DplSource::BeamsPointer &beamsPointer)
{
    qDebug("[%s:%s] debug here.", "TimeImageItem", __FUNCTION__);

    if((beamsShowedCount + 1) == commonProperties.maxIndex
            && (commonProperties.align != 0)) {
        /* 非对齐,最后一条beam */
        int offset =  commonProperties.pixCount - commonProperties.align;
        QImage tmp = m_image->copy(offset, 0, m_image->width(), m_image->height());
        m_image->swap(tmp);
        qDebug("[%s:%s] begin call set_vertical_image_data.", "TimeImageItem", __FUNCTION__);
        set_vertical_image_data(beamsShowedCount, commonProperties, LAST_BEAM, beamsPointer);

    } else {
        qDebug("[%s:%s] begin call set_vertical_image_data.", "TimeImageItem", __FUNCTION__);
        set_vertical_image_data(beamsShowedCount, commonProperties, NORMAL_BEAM, beamsPointer);
    }
}


void TimeImageItem::scroll_vertical_image(const BaseImageItem::S_CommonProperties &commonProperties,
                                     const DplSource::BeamsPointer &beamsPointer)
{
    QImage tmp = m_image->copy(commonProperties.pixCount, 0, m_image->width(), m_image->height());
    m_image->swap(tmp);

    set_vertical_image_data(0, commonProperties, LAST_BEAM, beamsPointer);
}


