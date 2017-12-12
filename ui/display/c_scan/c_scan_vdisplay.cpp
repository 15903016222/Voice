#include "c_scan_vdisplay.h"
#include "../scan_view.h"

CscanVDisplay::CscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : CscanDisplay(grp, Qt::Vertical, parent)
{
    init_ruler();
}


void CscanVDisplay::init_ruler()
{
    update_scan_type_ruler(m_view->size());

    update_law_type_ruler();
}


