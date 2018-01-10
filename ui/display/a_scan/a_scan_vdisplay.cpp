/**
 * @file a_scan_vdisplay.cpp
 * @brief A扫纵向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "a_scan_vdisplay.h"

#include "../base/scan_view.h"
#include "../ruler/amp_ruler.h"
#include "../ruler/ut_ruler.h"

AscanVDisplay::AscanVDisplay(const DplDevice::GroupPointer &group, QWidget *parent) :
    AscanDisplay(group, parent),
    m_ampRuler(new AmpRuler(Ruler::TOP, this)),
    m_utRuler(new UtRuler(group, Ruler::RIGHT, this))
{  
    m_view->set_orientation(Qt::Vertical);
    m_leftLayout->addWidget(m_utRuler);
    m_bottomLayout->addWidget(m_ampRuler);
}
