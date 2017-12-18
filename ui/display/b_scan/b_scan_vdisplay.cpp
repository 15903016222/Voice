#include "b_scan_vdisplay.h"

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../ruler/ut_ruler.h"
#include "../ruler/scan_ruler.h"

BscanVDisplay::BscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    BscanDisplay(grp, parent),
    m_utRuler(new UtRuler(grp, Ruler::RIGHT, this)),
    m_scanRuler(new ScanRuler(grp, Ruler::TOP, this))
{
    m_view->rotate(90);
    m_leftLayout->addWidget(m_utRuler);
    m_bottomLayout->addWidget(m_scanRuler);
}

void BscanVDisplay::resize_event(const QSize &size)
{
    m_scene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                               size.height(), size.width());
    m_bscanItem->set_size(QSize(size.height(), size.width()));
    BscanDisplay::resize_event(size);
}
