#include "c_scan_hdisplay.h"
#include "c_scan_item.h"

#include "../base/scan_scene.h"
#include "../ruler/scan_ruler.h"
#include "../ruler/index_ruler.h"

CscanHDisplay::CscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    CscanDisplay(grp, parent),
    m_scanRuler(new ScanRuler(grp, Ruler::RIGHT, this)),
    m_indexRuler(new IndexRuler(grp, Ruler::TOP, this))
{
    m_leftLayout->addWidget(m_indexRuler);
    m_bottomLayout->addWidget(m_scanRuler);
}

void CscanHDisplay::resize_event(const QSize &size)
{
    m_scene->setSceneRect(-size.width()/2.0, -size.height()/2.0,
                               size.width(), size.height());

    m_cscanItem->set_size(size);

    CscanDisplay::resize_event(size);
}

