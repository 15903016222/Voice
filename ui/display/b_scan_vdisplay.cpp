#include "b_scan_vdisplay.h"
#include "ui_b_scan_display.h"
#include "source/source.h"
#include "source/scan.h"
#include "scan_view.h"
#include "b_scan_scene.h"

#include "ui/display/Tracer.h"

BscanVDisplay::BscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, Qt::Vertical, parent)
{
    init_ruler();
}


void BscanVDisplay::init_ruler()
{
    DEBUG_INIT("BscanVDisplay", __FUNCTION__);

    m_soundPathRuler = ui->leftRuler;
    m_scanTypeRuler  = ui->bottomRuler;

    m_soundPathRuler->set_type(RulerWidget::LEFT);
    m_soundPathRuler->set_direction(RulerWidget::Up);

#if 0
    if(m_bscanScene->driving() == DplSource::Axis::ENCODER_X
        || m_bscanScene->driving() == DplSource::Axis::ENCODER_Y) {

        double scanStart        = DplSource::Scan::instance()->scan_axis()->start();
        double scanEnd          = DplSource::Scan::instance()->scan_axis()->end();
        double scanRosolution   = DplSource::Scan::instance()->scan_axis()->resolution();

        /* 扫查轴 */
        /* 根据scan start/end 及resolution（扫查分辨率）计算待显示的总beam数 */
        double beamCount = (int)((scanEnd - scanStart) / scanRosolution + 0.5);
        int width = m_scanTypeRuler->width();

        if(width > beamCount) {
            /* 若显示区域大于beam数，则计算每条beam占多少pix */
            double pixCount = width / beamCount + 0.5;
            m_scanTypeRuler->set_range(scanStart, scanEnd);
            m_bscanScene->set_pix_per_beam(pixCount);

        } else {
            m_scanTypeRuler->set_range(scanStart, scanStart + width);
            m_bscanScene->set_pix_per_beam(DEFAULT_PIX_PER_BEAM);
        }

        m_scanTypeRuler->set_unit("(mm)");


    } else {

        m_scanTypeRuler->set_range(0.0, m_bscanView->width() * m_pixPerBeam);
        m_scanTypeRuler->set_unit("(s)");
    }
#else

    update_scan_type_ruler(m_bscanView->size());

#endif

    update_sound_path_ruler();

}
