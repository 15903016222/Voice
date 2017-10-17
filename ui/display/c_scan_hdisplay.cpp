#include "c_scan_hdisplay.h"
#include "ui_scan_display.h"
#include "scan_view.h"
#include "scroll_ruler_widget.h"

CscanHDisplay::CscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : CscanDisplay(grp, Qt::Horizontal, parent)
{
     init_ruler();
}

void CscanHDisplay::init_ruler()
{
    m_lawTypeRuler->set_type(RulerWidget::BOTTOM);
    m_lawTypeRuler->set_direction(RulerWidget::Up);

    m_scanTypeRuler->set_type(RulerWidget::LEFT);
    m_scanTypeRuler->set_direction(RulerWidget::Down);

    update_scan_type_ruler(m_view->size());

    update_law_type_ruler();
}
