#include "b_scan_hdisplay.h"

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
