/**
 * @file a_scan_hdisplay.cpp
 * @brief A扫横向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "a_scan_hdisplay.h"
#include "tcg_item.h"
#include "wave_item.h"

#include "../base/scan_scene.h"

AscanHDisplay::AscanHDisplay(const DplDevice::GroupPointer &group, QWidget *parent) :
    AscanDisplay(group, parent)
{
    init_amplitude_ruler();
    init_ultrasound_ruler();
}

Ruler *AscanHDisplay::amplitude_ruler() const
{
    qDebug("%s[%d]: ",__func__, __LINE__);
    return m_leftRuler;
}

Ruler *AscanHDisplay::ultrasound_ruler() const
{
    qDebug("%s[%d]: ",__func__, __LINE__);
    return m_bottomRuler;
}

void AscanHDisplay::resize_event(const QSize &size)
{    
    m_scene->setSceneRect(-size.width()/2, -size.height()/2,
                          size.width(), size.height());

    m_waveItem->set_size(size);
    m_tcgItem->set_size(size);

    AscanDisplay::resize_event(size);
}
