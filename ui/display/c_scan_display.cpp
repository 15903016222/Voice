#include "c_scan_display.h"
#include "ui_scan_display.h"


#include "c_scan_scene.h"
#include "c_scan_encoder_scene.h"
#include "c_scan_time_scene.h"
#include "scroll_ruler_widget.h"
#include "scan_view.h"

#include <device/device.h>
#include <source/axis.h>
#include <source/scan.h>
#include <source/source.h>

#include <QDebug>

static const double SECOND = 1000.0;

CscanDisplay::CscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanDisplay),
    m_group(grp),
    m_view(new ScanView),
    m_scene(NULL),
    m_orientation(orientation),
    m_currentTimeCount(0.0)
{
    ui->setupUi(this);

    ui->scanLayout->addWidget(m_view);

    init_scan_env();

    connect(m_view, SIGNAL(size_changed(QSize)),
            m_scene, SLOT(set_size(QSize)));
    connect(m_view, SIGNAL(size_changed(QSize)),
            this, SLOT(do_view_size_changed(QSize)));

    m_view->setScene(m_scene);

    init_ruler();

    ui->colorBarWidget->set_palette(DplDevice::Device::instance()->display()->palette());
    ui->titleLabel->setText(QString("C-Scan|Grp%1").arg(m_group->index()+1));

    /* source setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    connect(this, SIGNAL(refresh_scan_env()), this, SLOT(do_refresh_scan_env()));
    connect(this, SIGNAL(update_ruler(double)), this, SLOT(do_update_ruler(double)));

}

CscanDisplay::~CscanDisplay()
{
    delete ui;
    delete m_view;
    delete m_scene;
}

void CscanDisplay::do_data_event(const DplSource::BeamsPointer &beams)
{
    if(m_scene->width() == 0
            || m_scene->height() == 0) {
        qDebug("[%s] w/h is 0.", __FUNCTION__);
        return;
    }

    if(beams.isNull()) {
        qDebug("[%s] beams is NULL.", __FUNCTION__);
        return;
    }

    DplFocallaw::ProbePointer probe = m_group->focallawer()->probe();
    if((!probe.isNull()) && probe->is_pa()) {
        DplFocallaw::PaProbePointer paProbe = probe.staticCast<DplFocallaw::PaProbe>();
        m_scanCnfPointer = paProbe->scan_configure();
    }

    if(m_scene->need_refresh(beams) || focallaw_mode_changed()) {
        emit refresh_scan_env();
        wait_for_refresh_finished();
    }

    if(m_scene->driving() == DplSource::Axis::TIMER) {
        draw_timer_beams(beams);
    } else {
        draw_encoder_beams(beams);
    }
}

void CscanDisplay::init_ruler()
{
    if(m_orientation == Qt::Vertical) {
        m_scanTypeRuler = ui->bottomRulerWidget;
        m_lawTypeRuler  = ui->leftRulerWidget;
    } else {
        m_scanTypeRuler = ui->leftRulerWidget;
        m_lawTypeRuler  = ui->bottomRulerWidget;
    }

    ui->rightRulerWidget->set_type(RulerWidget::RIGHT);
    ui->rightRulerWidget->set_direction(RulerWidget::Down);
    ui->rightRulerWidget->set_range(0, 100);
    ui->rightRulerWidget->set_unit("(%)");
    ui->rightRulerWidget->update();

}

void CscanDisplay::update_scan_type_ruler(const QSize &size)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    if(m_scene->driving() == DplSource::Axis::ENCODER_X
           || m_scene->driving() == DplSource::Axis::ENCODER_Y) {

        /* 扫查轴 */
        /* 根据scan start/end 及resolution（扫查分辨率）计算待显示的总beam数 */

        double scanStart        = DplSource::Scan::instance()->scan_axis()->start();
        double scanEnd          = DplSource::Scan::instance()->scan_axis()->end();
        double scanResolution   = DplSource::Scan::instance()->scan_axis()->resolution();

        double beamCount = (scanEnd - scanStart) / scanResolution;

        int width;
        if(m_orientation == Qt::Horizontal) {
            width = size.height();
        } else {
            width = size.width();
        }

        if(width >= beamCount) {
            /* 若显示区域大于beam数，则计算每条beam占多少pix */
            double pixCount = width / beamCount;
            m_scanTypeRuler->set_range(scanStart, scanEnd);
            m_scanTypeRuler->set_max_end(scanEnd);
            m_scene->set_pix_per_beam(pixCount);
            m_scene->set_scroll_window(false);
            m_scanTypeRuler->set_show_range(scanStart, scanEnd);

        } else {
            /* 若显示区域小于beam数，则计算每条beam占一个pix */
            m_scanTypeRuler->set_range(scanStart, scanStart + width);
            m_scanTypeRuler->set_max_end(scanEnd);
            m_scene->set_pix_per_beam(DEFAULT_PIX_PER_BEAM);
            m_scene->set_scroll_window(true);
            m_scanTypeRuler->set_show_range(scanStart, scanStart + width);
        }

        m_scanTypeRuler->set_unit("(mm)");

    } else {

        double scanTypeRulerEnd;

        double beamQtyPerSecond = SECOND / (double)DplSource::Source::instance()->interval();

        if(m_orientation == Qt::Horizontal) {
            scanTypeRulerEnd = size.height() / beamQtyPerSecond;
        } else {
            scanTypeRulerEnd = size.width() / beamQtyPerSecond;
        }

        m_scanTypeRuler->set_range(0.0, scanTypeRulerEnd);
        m_scanTypeRuler->set_unit("(s)");
    }

    m_scanTypeRuler->update();
}

void CscanDisplay::update_law_type_ruler()
{
    const DplFocallaw::ProbePointer &probe = m_group->focallawer()->probe();

    if(probe->is_pa()) {

        qDebug() << "[" << __FUNCTION__ << "]" << " is PA. beam qty = " << m_group->focallawer()->beam_qty();

        DplFocallaw::PaProbe *paProbe = static_cast<DplFocallaw::PaProbe * > (probe.data());

        if(paProbe != NULL) {

            qDebug() << "[" << __FUNCTION__ << "]" << " PA: mode is " << paProbe->scan_configure()->mode();

            if(paProbe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
                /* 线扫 */
                m_lawTypeRuler->set_range(0.0, m_group->focallawer()->beam_qty());
                m_lawTypeRuler->set_unit("(VPA)");

            } else {
                /* 扇扫 */
                /* 获取起始角度、终止角度 */

                 DplFocallaw::SectorialScanCnf *sectorialScanCnf =
                         static_cast<DplFocallaw::SectorialScanCnf *> (paProbe->scan_configure().data());
                 if(sectorialScanCnf) {
                    double startAngle = sectorialScanCnf->first_angle();
                    double lastAngle  = sectorialScanCnf->last_angle();
                    double stepAngle  = sectorialScanCnf->angle_step();
                    double beamQty    = (startAngle - lastAngle) / stepAngle + 1.0;
                 }

                 m_lawTypeRuler->set_range(0.0, m_group->focallawer()->beam_qty());
                 m_lawTypeRuler->set_unit("(°)");
            }
        }
    }

    m_lawTypeRuler->update();
}

void CscanDisplay::wait_for_refresh_finished()
{
    m_refreshSemaphore.acquire(m_refreshSemaphore.available() + 1);
}

void CscanDisplay::do_refresh_scan_env()
{
    init_scan_env();

    update_scan_type_ruler(m_view->size());

    update_law_type_ruler();

    m_refreshSemaphore.release();
}

void CscanDisplay::do_view_size_changed(const QSize &size)
{
    if (m_orientation == Qt::Horizontal) {

        m_scene->set_size(QSize(size.height(), size.width()));

    } else {

        m_scene->set_size(QSize(size.width(), size.height()));
    }

    update_scan_type_ruler(size);
}

void CscanDisplay::do_update_ruler(double value)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    m_scanTypeRuler->update();
}

void CscanDisplay::init_scan_env()
{
    if(m_scene != NULL) {
        delete m_scene;
        m_scene = NULL;
    }

    if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::TIMER) {
        m_scene = new CscanTimeScene(DplDevice::Device::instance()->display()->palette(), m_group);
        m_currentTimeCount = 0.0;

    } else {
        m_scene = new CscanEncoderScene(DplDevice::Device::instance()->display()->palette(), m_group);
    }

    ui->scanLayout->addWidget(m_view);
    m_view->setScene(m_scene);

    if (m_orientation == Qt::Horizontal) {
        m_scene->set_size(QSize(m_view->height(), m_view->width()));
    } else {
        m_scene->set_size(m_view->size());
    }
}

bool CscanDisplay::focallaw_mode_changed()
{
    if(m_scanCnfPointer->mode() == m_focallawMode) {
        m_focallawMode = m_scanCnfPointer->mode();
        return false;
    }

    m_focallawMode = m_scanCnfPointer->mode();
    return true;
}

void CscanDisplay::draw_timer_beams(const DplSource::BeamsPointer &beams)
{
    m_scene->redraw_beams();

    m_currentTimeCount += DplSource::Source::instance()->interval() / 1000.0;
    double rulerEnd;
    if(m_orientation == Qt::Horizontal) {
        rulerEnd = m_view->height() / (SECOND / (double)DplSource::Source::instance()->interval());
    } else {
        rulerEnd = m_view->width() / (SECOND / (double)DplSource::Source::instance()->interval());
    }

    m_scene->set_beams(beams);

    if(m_currentTimeCount > rulerEnd) {
        m_scene->set_scroll_window(true);
        m_scanTypeRuler->move_to_value(m_currentTimeCount);
        emit update_ruler(m_currentTimeCount);
    }
}

void CscanDisplay::draw_encoder_beams(const DplSource::BeamsPointer &beams)
{
    if(m_scene->redraw_beams()) {

        CscanEncoderScene *scene = static_cast<CscanEncoderScene*> (m_scene);
        if(scene) {
            m_scanTypeRuler->set_show_range(scene->show_start(), scene->show_end());
        }
    }

    double x;

    if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::ENCODER_X) {
        x = ((int)((beams->get(0)->encoder_x() / DplSource::Scan::instance()->encoder_x()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
    } else {
        x = ((int)((beams->get(0)->encoder_y() / DplSource::Scan::instance()->encoder_y()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
    }

    m_scene->set_beams(beams);
    m_scanTypeRuler->move_to_value(x);
    emit update_ruler(x);
}
