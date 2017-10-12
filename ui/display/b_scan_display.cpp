#include "b_scan_display.h"
#include "ui_b_scan_display.h"

#include <QTimer>

#include "source/beams.h"
#include "source/scan.h"
#include "source/source.h"
#include "device/device.h"
#include "fpga/fpga.h"

#include "scan_view.h"
#include "b_scan_scene.h"
#include "global.h"
#include "scroll_ruler_widget.h"
#include "b_scan_encoder_scene.h"
#include "b_scan_time_scene.h"

#include "Tracer.h"

static const double SECOND = 1000.0;

BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BscanDisplay),
    m_group(grp),
    m_scanTypeRuler(NULL),
    m_soundPathRuler(NULL),
    m_bscanView(new ScanView),
    m_bscanScene(NULL),
    m_currentTimeCount(0.0),
    m_orientation(orientation)
{
    ui->setupUi(this);

    ui->colorBar->set_palette(DplDevice::Device::instance()->display()->palette());

    init_ruler();

    connect(m_bscanView, SIGNAL(size_changed(QSize)),
            this, SLOT(do_view_size_changed(QSize)));

    ui->bScanWidgetVerticalLayout->addWidget(m_bscanView);

    connect(this, SIGNAL(update_ruler(double)), this, SLOT(do_update_ruler(double)));
    connect(this, SIGNAL(update_label(QString)), this, SLOT(do_update_label(QString)));
    connect(this, SIGNAL(refresh_scan_env()), this, SLOT(do_refresh_scan_env()));

    /* source setting */
    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    ui->titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));

    if(m_orientation == Qt::Horizontal) {
        m_bscanView->rotate(-90);
    }

    init_scan_env();

    if (m_orientation == Qt::Horizontal) {
        m_bscanScene->set_size(QSize(m_bscanView->height(), m_bscanView->width()));
    } else {
        m_bscanScene->set_size(QSize(m_bscanView->width(), m_bscanView->height()));
    }


}

BscanDisplay::~BscanDisplay()
{
    delete ui;

    delete m_bscanScene;
    delete m_bscanView;
}

bool BscanDisplay::set_current_beam(unsigned int index)
{
   return m_bscanScene->set_current_beam(index);
}


void BscanDisplay::init_ruler()
{
    DEBUG_INIT("BscanDisplay", __FUNCTION__);

    /* ruler setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_sound_path_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_sound_path_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_sound_path_ruler()));

    ui->rightRuler->set_type(RulerWidget::RIGHT);
    ui->rightRuler->set_direction(RulerWidget::Down);
    ui->rightRuler->set_range(0, 100);
    ui->rightRuler->set_unit("(%)");
    ui->rightRuler->update();

    if(m_orientation == Qt::Vertical) {
        m_soundPathRuler = ui->leftRuler;
        m_scanTypeRuler  = ui->bottomRuler;
    } else {
        m_soundPathRuler = ui->bottomRuler;
        m_scanTypeRuler  = ui->leftRuler;
    }
}


void BscanDisplay::do_data_event(const DplSource::BeamsPointer &beams)
{
    DEBUG_INIT("BscanDisplay", __FUNCTION__);

    if(m_bscanScene->width() == 0
            || m_bscanScene->height() == 0) {
        qDebug("[%s] w/h is 0.", __FUNCTION__);
        return;
    }

    if(beams.isNull()) {
        qDebug("[%s] beams is NULL.", __FUNCTION__);
        return;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " scan_axis driving = " << DplSource::Scan::instance()->scan_axis()->driving()
             << " scene driving = " << m_bscanScene->driving();
    if(m_bscanScene->need_refresh()) {
        emit refresh_scan_env();
        wait_for_refresh_finished();
    }

    if(m_bscanScene->driving() == DplSource::Axis::TIMER) {

        m_bscanScene->redraw_beams();

        m_currentTimeCount += DplSource::Source::instance()->interval() / 1000.0;
        double rulerEnd;

        if(m_orientation == Qt::Horizontal) {
            rulerEnd = m_bscanView->height() / (SECOND / (double)DplSource::Source::instance()->interval());
        } else {
            rulerEnd = m_bscanView->width() / (SECOND / (double)DplSource::Source::instance()->interval());
        }

        qDebug() << "[" << __FUNCTION__ << "]"
                 << "begin set_beams.";

        m_bscanScene->set_beams(beams);

        if(m_currentTimeCount > rulerEnd) {
            m_bscanScene->set_scroll_window(true);
            m_scanTypeRuler->move_to_value(m_currentTimeCount);
            emit update_ruler(m_currentTimeCount);
        }

        emit update_label(QString::number(m_currentTimeCount, 'f', 1));

    } else {

        if(m_bscanScene->redraw_beams()) {
            BscanEncoderScene *scene = static_cast<BscanEncoderScene*> (m_bscanScene);
            if(scene) {
                qDebug() << "[" << __FUNCTION__ << "]" << " current X = " << scene->move_x();
                m_scanTypeRuler->set_show_range(scene->show_start(), scene->show_end());
                //emit update_ruler(scene->move_x());
            }
        }

        double x;

        qDebug() << "[" << __FUNCTION__ << "]"
                 << " x = " << beams->get(0)->encoder_x()
                 << " y = " << beams->get(0)->encoder_y()
                 << " x true = " << beams->get(0)->encoder_x() / DplSource::Scan::instance()->encoder_x()->resolution()
                 << " y true = " << beams->get(0)->encoder_y() / DplSource::Scan::instance()->encoder_y()->resolution();

        if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::ENCODER_X) {
            x = ((int)((beams->get(0)->encoder_x() / DplSource::Scan::instance()->encoder_x()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
        } else {
            x = ((int)((beams->get(0)->encoder_y() / DplSource::Scan::instance()->encoder_y()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
        }

        m_bscanScene->set_beams(beams);
        m_scanTypeRuler->move_to_value(x);
        emit update_ruler(x);
    }
}

void BscanDisplay::do_update_ruler(double value)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    qDebug() << "[" << __FUNCTION__ << "]"
             << " update ruler x = " << value;
//    m_scanTypeRuler->move_to_value(value);
    m_scanTypeRuler->update();
}


void BscanDisplay::update_scan_type_ruler(const QSize &size)
{
    DEBUG_INIT("BscanDisplay", __FUNCTION__);

    if(m_scanTypeRuler == NULL) {
        return;
    }

    if(m_bscanScene->driving() == DplSource::Axis::ENCODER_X
           || m_bscanScene->driving() == DplSource::Axis::ENCODER_Y) {

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
            m_bscanScene->set_pix_per_beam(pixCount);
            m_bscanScene->set_scroll_window(false);
            m_scanTypeRuler->set_show_range(scanStart, scanEnd);

        } else {
            /* 若显示区域小于beam数，则计算每条beam占一个pix */
            m_scanTypeRuler->set_range(scanStart, scanStart + width);
            m_scanTypeRuler->set_max_end(scanEnd);
            m_bscanScene->set_pix_per_beam(DEFAULT_PIX_PER_BEAM);
            m_bscanScene->set_scroll_window(true);
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

void BscanDisplay::wait_for_refresh_finished()
{
    DEBUG_INIT("BscanDisplay", __FUNCTION__);

    m_refreshSemaphore.acquire(m_refreshSemaphore.available() + 1);
}

void BscanDisplay::init_scan_env()
{
    if(m_bscanScene != NULL) {
        delete m_bscanScene;
        m_bscanScene = NULL;
    }

    if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::TIMER) {
        m_bscanScene = new BscanTimeScene(DplDevice::Device::instance()->display()->palette(), m_group->index());
        m_currentTimeCount = 0.0;

    } else {
        m_bscanScene = new BscanEncoderScene(DplDevice::Device::instance()->display()->palette(), m_group->index());
    }

    ui->bScanWidgetVerticalLayout->addWidget(m_bscanView);
    m_bscanView->setScene(m_bscanScene);

    if (m_orientation == Qt::Horizontal) {
        m_bscanScene->set_size(QSize(m_bscanView->height(), m_bscanView->width()));
    } else {
        m_bscanScene->set_size(m_bscanView->size());
    }
}


void BscanDisplay::do_refresh_scan_env()
{
    DEBUG_INIT("BscanDisplay", __FUNCTION__);

    init_scan_env();

    update_scan_type_ruler(m_bscanView->size());

    m_refreshSemaphore.release();
}

void BscanDisplay::update_sound_path_ruler()
{
    DEBUG_INIT("BscanDisplay", __FUNCTION__);

    if(m_soundPathRuler == NULL) {
        return;
    }

    double start = m_group->sample()->start();
    double end = (start + m_group->sample()->range());

    qDebug("%s[%d]: start(%f) end(%f) precision(%f)",__func__, __LINE__, start, end, m_group->sample()->precision());

    start = Dpl::ns_to_us(start);
    end = Dpl::ns_to_us(end);

    DplDevice::Group::UtUnit unit = m_group->ut_unit();

    if (DplDevice::Group::Time == unit) {
        m_soundPathRuler->set_unit("(us)");
        m_soundPathRuler->set_backgroup_color(QColor("#F9CCE2"));
    } else{
        ui->leftRuler->set_unit("(mm)");
        start *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
        start /= 2;
        end   *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
        end /= 2;
        m_soundPathRuler->set_backgroup_color(QColor("#f29cb1"));
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            m_soundPathRuler->set_backgroup_color(QColor("#ff00ff"));
        }
    }

    m_soundPathRuler->set_range(start, end);

    m_soundPathRuler->update();

    qDebug("%s[%d]: start(%f) end(%f) precision(%f)",__func__, __LINE__, start, end, m_group->sample()->precision());
}


void BscanDisplay::do_update_label(const QString &time)
{
    ui->label->setText(time);
}


void BscanDisplay::do_view_size_changed(const QSize &size)
{
    DEBUG_INIT("BscanDisplay", __FUNCTION__);

    if (m_orientation == Qt::Horizontal) {

        m_bscanScene->set_size(QSize(size.height(), size.width()));

    } else {

        m_bscanScene->set_size(QSize(size.width(), size.height()));
    }

    update_scan_type_ruler(size);
}

