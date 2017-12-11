#include "c_scan_hdisplay.h"
#include "ui_scan_display.h"
#include "../scan_view.h"

CscanHDisplay::CscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : CscanDisplay(grp, Qt::Horizontal, parent)
{
     init_ruler();
}

void CscanHDisplay::init_ruler()
{
    update_scan_type_ruler(m_view->size());

    update_law_type_ruler();
}
