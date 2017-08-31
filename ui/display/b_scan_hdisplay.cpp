#include "b_scan_hdisplay.h"
#include "ui_b_scan_display.h"
#include "b_scan_scene.h"
#include "scan_view.h"


BscanHDisplay::BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, Qt::Horizontal, parent)
{
    init_ruler();

    m_pixPerBeam = 1.0;
    m_bscanScene->set_pix_per_beam(m_pixPerBeam);
}

bool BscanHDisplay::set_scan_type(BscanDisplay::E_SCAN_TYPE type)
{
    BscanDisplay::set_scan_type(type);
    return true;
}


void BscanHDisplay::init_ruler()
{
    m_soundPathRuler = ui->bottomRuler;
    m_scanTypeRuler  = ui->leftRuler;

    m_soundPathRuler->set_type(RulerWidget::BOTTOM);
    m_soundPathRuler->set_direction(RulerWidget::Up);

    m_scanTypeRuler->set_type(RulerWidget::LEFT);
    m_scanTypeRuler->set_direction(RulerWidget::Down);

    if(m_type == ENCODER) {

        /* 扫查轴 */
        /* 根据scan start/end 及resolution（扫查分辨率）计算待显示的总beam数 */
        double beamCount = (int)((SCAN_END - SCAN_START) / SCAN_RESOLUTION + 0.5);
        int width;
        if(m_orientation == Qt::Horizontal) {
            width = m_scanTypeRuler->height();
        } else {
            width = m_scanTypeRuler->width();
        }

        if(width > beamCount) {
            /* 若显示区域大于beam数，则计算每条beam占多少pix */
            double pixCount = width / beamCount + 0.5;
            m_scanTypeRuler->set_range(SCAN_START, SCAN_END);
            m_bscanScene->set_pix_per_beam(pixCount);

        } else {
            m_scanTypeRuler->set_range(SCAN_START, SCAN_START + width);
            m_bscanScene->set_pix_per_beam(MIN_PIX_COUNT);
        }

        m_scanTypeRuler->set_unit("(mm)");

    } else {

        m_scanTypeRuler->set_range(0, m_bscanView->width() * m_pixPerBeam);
        m_scanTypeRuler->set_unit("(s)");
    }

    update_sound_path_ruler();
}
