#include "c_scan_vdisplay.h"
#include "ui_scan_display.h"

CscanVDisplay::CscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : CscanDisplay(grp, Qt::Vertical, parent)
{
    init_ruler();
}

void CscanVDisplay::init_ruler()
{
    m_lawTypeRuler->set_type(RulerWidget::LEFT);
}


