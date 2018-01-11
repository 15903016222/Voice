#include "b_scan_vdisplay.h"

#include "../base/scan_view.h"
#include "../ruler/ut_ruler.h"
#include "../ruler/scan_ruler.h"

BscanVDisplay::BscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    BscanDisplay(grp, parent),
    m_utRuler(new UtRuler(grp, Ruler::RIGHT, this)),
    m_scanRuler(new ScanRuler(grp, Ruler::TOP, this))
{
    m_view->set_orientation(Qt::Vertical);
    m_leftLayout->addWidget(m_utRuler);
    m_bottomLayout->addWidget(m_scanRuler);
}
