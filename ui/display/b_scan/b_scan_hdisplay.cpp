#include "b_scan_hdisplay.h"

#include "../base/scan_scene.h"
#include "../ruler/ut_ruler.h"
#include "../ruler/scan_ruler.h"

BscanHDisplay::BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    BscanDisplay(grp, parent),
    m_utRuler(new UtRuler(grp, Ruler::TOP, this)),
    m_scanRuler(new ScanRuler(grp, Ruler::RIGHT, this))
{
    m_leftLayout->addWidget(m_scanRuler);
    m_bottomLayout->addWidget(m_utRuler);
}

void BscanHDisplay::resize_event(const QSize &size)
{
    m_scene->setSceneRect(-size.width()/2.0, -size.height()/2.0,
                               size.width(), size.height());
    BscanDisplay::resize_event(size);
}
