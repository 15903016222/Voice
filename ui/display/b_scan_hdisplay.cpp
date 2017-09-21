#include "b_scan_hdisplay.h"
#include "ui_b_scan_display.h"
#include "b_scan_scene.h"
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

    m_soundPathRuler = ui->bottomRuler;
    m_scanTypeRuler  = ui->leftRuler;

    m_soundPathRuler->set_type(RulerWidget::BOTTOM);
    m_soundPathRuler->set_direction(RulerWidget::Up);

    m_scanTypeRuler->set_type(RulerWidget::LEFT);
    m_scanTypeRuler->set_direction(RulerWidget::Down);

#if 0
    if(m_bscanScene->driving() == DplSource::Axis::ENCODER_X
            || m_bscanScene->driving() == DplSource::Axis::ENCODER_Y) {

        /* 扫查轴 */
        /* 根据scan start/end 及resolution（扫查分辨率）计算待显示的总beam数 */
        double beamCount = (int)((DplSource::Scan::instance()->scan_axis()->end()
                                  - DplSource::Scan::instance()->scan_axis()->start())
                                 / DplSource::Scan::instance()->scan_axis()->resolution() + 0.5);
        int width;
        if(m_orientation == Qt::Horizontal) {
            width = m_scanTypeRuler->height();
        } else {
            width = m_scanTypeRuler->width();
        }

        if(width > beamCount) {
            /* 若显示区域大于beam数，则计算每条beam占多少pix */
            double pixCount = width / beamCount + 0.5;
            m_scanTypeRuler->set_range(DplSource::Scan::instance()->scan_axis()->start(),
                                       DplSource::Scan::instance()->scan_axis()->end());
            m_bscanScene->set_pix_per_beam(pixCount);

        } else {
            m_scanTypeRuler->set_range(DplSource::Scan::instance()->scan_axis()->start(),
                                       DplSource::Scan::instance()->scan_axis()->start() + width);
            m_bscanScene->set_pix_per_beam(DEFAULT_PIX_PER_BEAM);
        }

        m_scanTypeRuler->set_unit("(mm)");

    } else {

        m_scanTypeRuler->set_range(0, m_bscanView->width() * m_pixPerBeam);
        m_scanTypeRuler->set_unit("(s)");
    }

    m_scanTypeRuler->update();

#else
    update_scan_type_ruler(m_bscanView->size());
#endif

    update_sound_path_ruler();
}
