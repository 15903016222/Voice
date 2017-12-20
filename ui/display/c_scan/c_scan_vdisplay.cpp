#include "c_scan_vdisplay.h"
#include "c_scan_item.h"

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../ruler/index_ruler.h"
#include "../ruler/scan_ruler.h"

CscanVDisplay::CscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    CscanDisplay(grp, parent),
    m_indexRuler(new IndexRuler(grp, Ruler::RIGHT, this)),
    m_scanRuler(new ScanRuler(grp, Ruler::TOP, this))
{
    m_view->rotate(90);
    m_leftLayout->addWidget(m_indexRuler);
    m_bottomLayout->addWidget(m_scanRuler);
}

void CscanVDisplay::resize_event(const QSize &size)
{
    m_scene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                               size.height(), size.width());
    m_cscanItem->set_size(QSize(size.height(), size.width()));
    CscanDisplay::resize_event(size);
}



