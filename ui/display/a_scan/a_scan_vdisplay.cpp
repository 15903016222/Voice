/**
 * @file a_scan_vdisplay.cpp
 * @brief A扫纵向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "a_scan_vdisplay.h"

#include "wave_item.h"
#include "tcg_item.h"

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../ruler/amp_ruler.h"
#include "../ruler/ut_ruler.h"

AscanVDisplay::AscanVDisplay(const DplDevice::GroupPointer &group, QWidget *parent) :
    AscanDisplay(group, parent),
    m_ampRuler(new AmpRuler(Ruler::TOP, this)),
    m_utRuler(new UtRuler(group, Ruler::RIGHT, this))
{  
    m_view->rotate(90);
    m_leftLayout->addWidget(m_utRuler);
    m_bottomLayout->addWidget(m_ampRuler);
}

void AscanVDisplay::resize_event(const QSize &size)
{
    m_scene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                               size.height(), size.width());

    m_waveItem->set_size(QSize(size.height(), size.width()));
    m_tcgItem->set_size(QSize(size.height(), size.width()));

    AscanDisplay::resize_event(size);
}
