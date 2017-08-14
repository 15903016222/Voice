#include "b_scan_vdisplay.h"
#include "ui_b_scan_display.h"
#include "source/source.h"
#include "scan_view.h"
#include "b_scan_scene.h"

BscanVDisplay::BscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, parent)
{
    init_ruler();

    m_bscanScene->set_direction(BscanScene::VERTICAL);
    m_pixPerBeam = 1.0;
    m_bscanScene->set_pix_per_beam(m_pixPerBeam);
}

void BscanVDisplay::init_ruler()
{
    m_soundPathRuler = ui->leftRuler;
    m_scanTypeRuler = ui->bottomRuler;

    if(m_type == ENCODER) {


    } else {

        m_soundPathRuler->set_type(RulerWidget::LEFT);
        m_soundPathRuler->set_direction(RulerWidget::Up);
        m_scanTypeRuler->set_range(0, m_bscanView->width() * m_pixPerBeam);
        int frameCount = 1000 / DplSource::Source::instance()->interval();
        m_scanTypeRuler->set_unit("(s)");
    }

    update_sound_path_ruler();

}
