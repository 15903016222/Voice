#include "b_scan_hdisplay.h"
#include "ui_b_scan_display.h"
#include "b_scan_scene.h"

BscanHDisplay::BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, parent)
{
    init_ruler();

    m_bscanScene->set_direction(BscanScene::HORIZONTAL);
    m_pixPerBeam = 1.0;
    m_bscanScene->set_pix_per_beam(m_pixPerBeam);
}

void BscanHDisplay::init_ruler()
{

}
