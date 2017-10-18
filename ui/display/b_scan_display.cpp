#include "b_scan_display.h"
#include "ui_b_scan_display.h"

#include <QTimer>

#include "source/beams.h"
#include "source/scan.h"
#include "source/source.h"
#include "device/device.h"
#include "fpga/fpga.h"

#include "scan_view.h"
#include "global.h"
#include "b_scan_scene.h"
#include "scroll_ruler_widget.h"
#include "b_scan_encoder_image_item.h"
#include "b_scan_time_image_item.h"


BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BscanDisplay),
    m_group(grp),
    m_scanTypeRuler(NULL),
    m_soundPathRuler(NULL),
    m_bscanView(new ScanView),
    m_bscanScene(new BscanScene),
    m_bscanImageItem(NULL),
    m_orientation(orientation)
{
    ui->setupUi(this);

    ui->bScanWidgetVerticalLayout->addWidget(m_bscanView);
    m_bscanView->setScene(m_bscanScene);

    init_scan_env();

    init_ruler();

    connect(m_bscanView, SIGNAL(size_changed(QSize)),
            this, SLOT(do_view_size_changed(QSize)));

    ui->colorBar->set_palette(DplDevice::Device::instance()->display()->palette());
    ui->titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));


    if(m_orientation == Qt::Horizontal) {
        m_bscanView->rotate(-90);
    }

    /* source setting */
    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    connect(this, SIGNAL(refresh_scan_env()), this, SLOT(do_refresh_scan_env()));
    connect(this, SIGNAL(update_ruler(double)), this, SLOT(do_update_ruler(double)));
}

BscanDisplay::~BscanDisplay()
{
    disconnect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)));

    disconnect(this, SIGNAL(refresh_scan_env()), this, SLOT(do_refresh_scan_env()));
    disconnect(this, SIGNAL(update_ruler(double)), this, SLOT(do_update_ruler(double)));


    delete ui;
    delete m_bscanScene;
    delete m_bscanView;

    m_bscanScene = NULL;
    m_bscanView = NULL;
}


void BscanDisplay::init_ruler()
{
    if(m_orientation == Qt::Vertical) {
        m_soundPathRuler = ui->leftRuler;
        m_scanTypeRuler  = ui->bottomRuler;
    } else {
        m_soundPathRuler = ui->bottomRuler;
        m_scanTypeRuler  = ui->leftRuler;
    }

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
}


void BscanDisplay::do_data_event(const DplSource::BeamsPointer &beams)
{
    if(m_bscanScene == NULL
            || m_bscanView == NULL
            || m_bscanImageItem == NULL) {
        return;
    }

    if(m_bscanScene->width() == 0
            || m_bscanScene->height() == 0) {
        qDebug("[%s] w/h is 0.", __FUNCTION__);
        return;
    }

    if(beams.isNull()) {
        qDebug("[%s] beams is NULL.", __FUNCTION__);
        return;
    }

    if(m_bscanImageItem->need_refresh(beams)) {
        emit refresh_scan_env();
        wait_for_refresh_finished();
    }

    if(m_bscanImageItem->driving() == DplSource::Axis::TIMER) {
        draw_timer_beams(beams);
    } else {
        draw_encoder_beams(beams);
    }
}

void BscanDisplay::do_update_ruler(double value)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    m_scanTypeRuler->update();
}


void BscanDisplay::update_scan_type_ruler(const QSize &size)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    if(m_bscanImageItem->driving() == DplSource::Axis::ENCODER_X
           || m_bscanImageItem->driving() == DplSource::Axis::ENCODER_Y) {

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
            m_bscanImageItem->set_pix_per_beam(pixCount);
            m_bscanImageItem->set_scroll_window(false);
            m_scanTypeRuler->set_show_range(scanStart, scanEnd);

        } else {
            /* 若显示区域小于beam数，则计算每条beam占一个pix */
            m_scanTypeRuler->set_range(scanStart, scanStart + width);
            m_scanTypeRuler->set_max_end(scanEnd);
            m_bscanImageItem->set_pix_per_beam(DEFAULT_PIX_PER_BEAM);
            m_bscanImageItem->set_scroll_window(true);
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
    m_refreshSemaphore.acquire(m_refreshSemaphore.available() + 1);
}

void BscanDisplay::init_scan_env()
{
    if(m_bscanImageItem != NULL) {
        m_bscanScene->removeItem(m_bscanImageItem);
        delete m_bscanImageItem;
        m_bscanImageItem = NULL;
    }

    if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::TIMER) {
        m_bscanImageItem = new BscanTimeImageItem(DplDevice::Device::instance()->display()->palette(), m_group);
    } else {
        m_bscanImageItem = new BscanEncoderImageItem(DplDevice::Device::instance()->display()->palette(), m_group);
    }

    m_bscanScene->addItem(m_bscanImageItem);

    if (m_orientation == Qt::Horizontal) {
        m_bscanImageItem->set_size(QSize(m_bscanView->height(), m_bscanView->width()));
    } else {
        m_bscanImageItem->set_size(m_bscanView->size());
    }
}

void BscanDisplay::draw_timer_beams(const DplSource::BeamsPointer &beams)
{
    double currentTimeCount = TestStub::instance()->get_time();
    double rulerEnd;
    if(m_orientation == Qt::Horizontal) {
        rulerEnd = m_bscanView->height() / (SECOND / (double)DplSource::Source::instance()->interval());
    } else {
        rulerEnd = m_bscanView->width() / (SECOND / (double)DplSource::Source::instance()->interval());
    }

    if(!m_bscanImageItem->redraw_beams(beams)) {
        m_bscanImageItem->set_beams(beams);
    }

    if(currentTimeCount > rulerEnd) {
        m_bscanImageItem->set_scroll_window(true);
        m_scanTypeRuler->move_to_value(currentTimeCount);
        emit update_ruler(currentTimeCount);
    }
}

void BscanDisplay::draw_encoder_beams(const DplSource::BeamsPointer &beams)
{
    if(m_bscanImageItem->redraw_beams(beams)) {
        BscanEncoderImageItem *imageItem = static_cast<BscanEncoderImageItem*> (m_bscanImageItem);
        if(imageItem) {
            m_scanTypeRuler->set_show_range(imageItem->show_start(), imageItem->show_end());
        }
    }

    double x;

    if(DplSource::Scan::instance()->scan_axis()->driving() == DplSource::Axis::ENCODER_X) {
        x = ((int)((beams->get(0)->encoder_x() / DplSource::Scan::instance()->encoder_x()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
    } else {
        x = ((int)((beams->get(0)->encoder_y() / DplSource::Scan::instance()->encoder_y()->resolution() + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
    }

    m_bscanImageItem->set_beams(beams);
    m_scanTypeRuler->move_to_value(x);
    emit update_ruler(x);
}


void BscanDisplay::do_refresh_scan_env()
{
    init_scan_env();

    update_scan_type_ruler(m_bscanView->size());

    update_sound_path_ruler();

    m_refreshSemaphore.release();
}

void BscanDisplay::update_sound_path_ruler()
{
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


void BscanDisplay::do_view_size_changed(const QSize &size)
{
    QTime time;
    time.restart();

    disconnect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)));

    if (m_orientation == Qt::Vertical) {

        m_bscanScene->setSceneRect(-size.width()/2.0, -size.height()/2.0,
                                   size.width(), size.height());
        m_bscanImageItem->set_size(size);

    } else {

        m_bscanScene->setSceneRect(-size.height()/2.0, -size.width()/2.0,
                                   size.height(), size.width());
        m_bscanImageItem->set_size(QSize(size.height(), size.width()));
    }


    update_scan_type_ruler(size);

    update();

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    qDebug("BscanDisplay:%s[%d]: Take Time: %d(ms)",__func__, __LINE__, time.elapsed());
}

