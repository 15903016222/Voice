/**
 * @file a_scan_hdisplay.cpp
 * @brief A扫横向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "a_scan_hdisplay.h"

#include "../ruler/amp_ruler.h"
#include "../ruler/ut_ruler.h"

AscanHDisplay::AscanHDisplay(const DplDevice::GroupPointer &group, QWidget *parent) :
    AscanDisplay(group, parent),
    m_ampRuler(new AmpRuler(Ruler::RIGHT, this)),
    m_utRuler(new UtRuler(group, Ruler::TOP, this))
{
    m_ampRuler->set_range(100, 0);
    m_leftLayout->addWidget(m_ampRuler);
    m_bottomLayout->addWidget(m_utRuler);
}
