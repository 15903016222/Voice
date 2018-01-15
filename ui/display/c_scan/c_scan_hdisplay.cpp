#include "c_scan_hdisplay.h"

#include "../ruler/scan_ruler.h"
#include "../ruler/index_ruler.h"
#include "../cursor/scan_ref_cursor_item.h"
#include "../cursor/scan_meas_cursor_item.h"

CscanHDisplay::CscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    CscanDisplay(grp, parent),
    m_scanRuler(new ScanRuler(grp, Ruler::RIGHT, this)),
    m_indexRuler(new IndexRuler(grp, Ruler::TOP, this))
{
    m_bottomLayout->addWidget(m_indexRuler);
    m_leftLayout->addWidget(m_scanRuler);

    connect(m_scanRuler, SIGNAL(start_changed(double, double)),
            scan_reference_cursor_item(),
            SLOT(set_visual_range(double,double)),
            Qt::QueuedConnection);
    connect(m_scanRuler, SIGNAL(start_changed(double,double)),
            scan_measurement_cursor_item(),
            SLOT(set_visual_range(double,double)),
            Qt::QueuedConnection);
}
