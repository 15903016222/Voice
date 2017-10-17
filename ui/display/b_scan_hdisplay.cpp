#include "b_scan_hdisplay.h"
#include "ui_b_scan_display.h"
#include "scan_view.h"
#include "source/scan.h"

#include "ui/display/Tracer.h"


BscanHDisplay::BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, Qt::Horizontal, parent)
{
    init_ruler();
}


void BscanHDisplay::init_ruler()
{
    DEBUG_INIT("BscanHDisplay", __FUNCTION__);

    m_soundPathRuler->set_type(RulerWidget::BOTTOM);
    m_soundPathRuler->set_direction(RulerWidget::Up);

    m_scanTypeRuler->set_type(RulerWidget::LEFT);
    m_scanTypeRuler->set_direction(RulerWidget::Down);

    update_scan_type_ruler(m_bscanView->size());

    update_sound_path_ruler();

}
