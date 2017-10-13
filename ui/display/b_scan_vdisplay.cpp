#include "b_scan_vdisplay.h"
#include "ui_b_scan_display.h"
#include "source/source.h"
#include "source/scan.h"
#include "scan_view.h"

#include "ui/display/Tracer.h"

BscanVDisplay::BscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, Qt::Vertical, parent)
{
    init_ruler();
}


void BscanVDisplay::init_ruler()
{
    DEBUG_INIT("BscanVDisplay", __FUNCTION__);

    m_soundPathRuler->set_type(RulerWidget::LEFT);
    m_soundPathRuler->set_direction(RulerWidget::Up);

    update_scan_type_ruler(m_bscanView->size());

    update_sound_path_ruler();

}
