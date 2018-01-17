#include "b_scan_hdisplay.h"

#include "../ruler/ut_ruler.h"
#include "../ruler/scan_ruler.h"
#include "../cursor/scan_ref_cursor_item.h"
#include "../cursor/scan_meas_cursor_item.h"

BscanHDisplay::BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    BscanDisplay(grp, parent),
    m_utRuler(new UtRuler(grp, Ruler::TOP, this)),
    m_scanRuler(new ScanRuler(grp, Ruler::RIGHT, this))
{
    m_leftLayout->addWidget(m_scanRuler);
    m_bottomLayout->addWidget(m_utRuler);

    connect(m_scanRuler, SIGNAL(start_changed(double, double)),
            scan_reference_cursor_item(),
            SLOT(set_visual_range(double,double)),
            Qt::QueuedConnection);
    connect(m_scanRuler, SIGNAL(start_changed(double,double)),
            scan_measurement_cursor_item(),
            SLOT(set_visual_range(double,double)),
            Qt::QueuedConnection);
}
