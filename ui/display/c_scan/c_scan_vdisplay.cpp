#include "c_scan_vdisplay.h"

#include "../base/scan_view.h"
#include "../ruler/index_ruler.h"
#include "../ruler/scan_ruler.h"
#include "../cursor/scan_ref_cursor_item.h"
#include "../cursor/scan_meas_cursor_item.h"

CscanVDisplay::CscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    CscanDisplay(grp, parent),
    m_indexRuler(new IndexRuler(grp, Ruler::RIGHT, this)),
    m_scanRuler(new ScanRuler(grp, Ruler::TOP, this))
{
    m_view->set_orientation(Qt::Vertical);
    m_leftLayout->addWidget(m_indexRuler);
    m_bottomLayout->addWidget(m_scanRuler);

    connect(m_scanRuler, SIGNAL(start_changed(double, double)),
            scan_reference_cursor_item(),
            SLOT(set_visual_range(double,double)),
            Qt::QueuedConnection);
    connect(m_scanRuler, SIGNAL(start_changed(double,double)),
            scan_measurement_cursor_item(),
            SLOT(set_visual_range(double,double)),
            Qt::QueuedConnection);
}

