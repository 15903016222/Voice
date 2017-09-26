#include "c_scan_time_scene.h"

#include <source/source.h>

CscanTimeScene::CscanTimeScene(const DplDisplay::PaletteColorPointer &palette, const DplDevice::GroupPointer &grp, QObject *parent)
    : CscanScene(palette, grp, parent)
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
    S_CommonProperties commonProperties;

    calculate_common_properties(commonProperties);

    if(m_scrolling) {
        /* 整个显示区域画满beam，开始滚动显示后续的beam */
        scroll_vertical_image(commonProperties);
    } else {
        set_vertical_image_data(m_beamsShowedCount, commonProperties, m_beamsPointer);
    }

    ++m_beamsShowedCount;
}


void CscanTimeScene::redraw_vertical_beam()
{
    if(!((m_beamsShowedCount > 0)
         && (!m_beamsPointer.isNull())
        && (m_image != NULL))) {
        return;
    }

    S_CommonProperties commonProperties;
    S_RedrawProperties redrawProperties;

    calculate_common_properties(commonProperties);
    calculate_redraw_properties(commonProperties, redrawProperties);

    DplSource::BeamsPointer tmp;
    int tmpBeamsShowedCount = 0;

    for(int i = 0; i < redrawProperties.redrawCount; ++i) {

        if(redrawProperties.beginShowIndex >= 0) {
            /* 顺序显示beams */
            tmp = DplSource::Source::instance()->beams(m_group->index(), redrawProperties.beginShowIndex + i);

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
}


