#include "c_scan_vdisplay.h"
#include "ui_scan_display.h"
#include "../scan_view.h"
#include "../scroll_ruler_widget.h"

CscanVDisplay::CscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : CscanDisplay(grp, Qt::Vertical, parent)
{
    init_ruler();
}


void CscanVDisplay::init_ruler()
{
    m_lawTypeRuler->set_type(RulerWidget::LEFT);

    update_scan_type_ruler(m_view->size());

    update_law_type_ruler();
}


