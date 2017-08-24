#include "b_scan_hdisplay.h"
#include "ui_b_scan_display.h"
#include "b_scan_scene.h"
#include "scan_view.h"


BscanHDisplay::BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, parent)
{
    init_ruler();

    m_bscanScene->set_direction(BscanScene::HORIZONTAL);
    m_pixPerBeam = 1.0;
    m_bscanScene->set_pix_per_beam(m_pixPerBeam);

}

bool BscanHDisplay::set_scan_type(BscanDisplay::E_SCAN_TYPE type)
{
    BscanDisplay::set_scan_type(type);

    m_bscanScene->set_direction(BscanScene::HORIZONTAL);

    return true;
}


void BscanHDisplay::init_ruler()
{
    m_soundPathRuler = ui->bottomRuler;
    m_scanTypeRuler  = ui->leftRuler;

    if(m_type == ENCODER) {


    } else {

        m_soundPathRuler->set_type(RulerWidget::BOTTOM);
        m_soundPathRuler->set_direction(RulerWidget::Up);

        m_scanTypeRuler->set_type(RulerWidget::LEFT);
        m_scanTypeRuler->set_direction(RulerWidget::Down);
        m_scanTypeRuler->set_range(0, m_bscanView->width() * m_pixPerBeam);
        m_scanTypeRuler->set_unit("(s)");
    }

    update_sound_path_ruler();
}
