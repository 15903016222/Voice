#include "c_scan_time_scene.h"

#include <source/source.h>

CscanTimeScene::CscanTimeScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent)
    : CscanScene(palette, grp, parent),
      m_currentTimeCount(0.0),
      m_pendingTimeCount(0.0)
{
    m_driving = DplSource::Axis::TIMER;
}

bool CscanTimeScene::need_refresh(const DplSource::BeamsPointer &beams)
{
    if(CscanScene::need_refresh(beams)) {
        return true;
    }

    return false;
}


void CscanTimeScene::draw_vertical_beam()
{
    m_pendingTimeCount = TestStub::instance()->get_time();

    S_CommonProperties commonProperties;

    calculate_common_properties(commonProperties);

    int pendingFrameCount = (m_pendingTimeCount * 1000) / DplSource::Source::instance()->interval();
    int totalFrameCount = STORE_BUFFER_SIZE / m_beamsPointer->size();

    DplSource::BeamsPointer beamsPointer = DplSource::Source::instance()->beams(m_group->index(),
                                                                                pendingFrameCount % totalFrameCount);

    qDebug() << "[" << __FUNCTION__ << "]" << " target frame index = " << pendingFrameCount % totalFrameCount;

    if(m_scrolling) {
        /* 整个显示区域画满beam，开始滚动显示后续的beam */
        scroll_vertical_image(commonProperties, beamsPointer);
    } else {
        set_vertical_image_data(m_beamsShowedCount, commonProperties, beamsPointer);
    }

    ++m_beamsShowedCount;
    m_currentTimeCount = m_pendingTimeCount;
}


bool CscanTimeScene::redraw_vertical_beam()
{
//    qDebug() << "[" << __FUNCTION__ << "]" << " m_beamsShowedCount = " << m_beamsShowedCount
//             << "  m_image = " << m_image
//             << " m_beamsPointer = " << m_beamsPointer.isNull();

    if(!((!m_beamsPointer.isNull())
        && (m_image != NULL))) {
        return false;
    }

    m_pendingTimeCount = TestStub::instance()->get_time();
    double timeSpace = m_pendingTimeCount - m_currentTimeCount;
    int beamsCount = (timeSpace * 1000) / DplSource::Source::instance()->interval();

    S_CommonProperties commonProperties;
    calculate_common_properties(commonProperties);

    S_RedrawProperties redrawProperties;

//    qDebug() << "[" << __FUNCTION__ << "]"
//             << " m_pendingTimeCount = " << m_pendingTimeCount
//             << " m_currentTimeCount = " << m_currentTimeCount
//             << " timeSpace = " << timeSpace;

//    qDebug() << "[" << __FUNCTION__ << "]"
//             << " beamsCount = " << beamsCount
//             << " maxIndex = " << commonProperties.maxIndex;

//    qDebug() << "[" << __FUNCTION__ << "]"
//             << " m_redrawFlag = " << m_redrawFlag;

    if(beamsCount > commonProperties.maxIndex) {

        int pendingFrameCount = m_pendingTimeCount * 1000 / DplSource::Source::instance()->interval();

        redrawProperties.currentFrameIndex  = pendingFrameCount;
        redrawProperties.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();
        redrawProperties.redrawCount        = commonProperties.maxIndex;
        redrawProperties.beginShowIndex     = redrawProperties.currentFrameIndex - redrawProperties.redrawCount + 1;

    } else if(beamsCount > 1) {

        int pendingFrameCount = m_pendingTimeCount * 1000 / DplSource::Source::instance()->interval();
        int currentFrameCount = m_currentTimeCount * 1000 / DplSource::Source::instance()->interval();

        redrawProperties.currentFrameIndex  = pendingFrameCount;
        redrawProperties.totalFrameCount    = STORE_BUFFER_SIZE / m_beamsPointer->size();
        redrawProperties.redrawCount        = pendingFrameCount - currentFrameCount;
        redrawProperties.beginShowIndex     = currentFrameCount;

    } else if(m_redrawFlag) {

        int pendingFrameCount = m_pendingTimeCount * 1000 / DplSource::Source::instance()->interval();

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

        qDebug() << "[" << __FUNCTION__ << "]" << " no need to redraw.";
        return false;
    }

//    qDebug() << "[" << __FUNCTION__ << "]"
//             << " currentFrameIndex = " << redrawProperties.currentFrameIndex
//             << " totalFrameCount = " << redrawProperties.totalFrameCount
//             << " redrawCount = " << redrawProperties.redrawCount
//             << " beginShowIndex = " << redrawProperties.beginShowIndex;

    DplSource::BeamsPointer tmp;
    int tmpBeamsShowedCount = 0;

    for(int i = 0; i < redrawProperties.redrawCount; ++i) {

        if(redrawProperties.beginShowIndex >= 0) {
            /* 顺序显示beams */
            tmp = DplSource::Source::instance()->beams(m_group->index(),
                                                       (redrawProperties.beginShowIndex + i) % redrawProperties.totalFrameCount);

        } else {
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
        }

        if(tmp.isNull()) {

            qDebug() << "[" << __FUNCTION__ << "]" << " BeamsPointer is NULL. tmpBeamsShowedCount = " << tmpBeamsShowedCount;
        }

        set_vertical_image_data(tmpBeamsShowedCount, commonProperties, tmp);

        ++tmpBeamsShowedCount;
    }

    m_beamsShowedCount = tmpBeamsShowedCount;
    m_currentTimeCount = m_pendingTimeCount;
    m_redrawFlag = false;

    return true;
}


