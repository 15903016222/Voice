#include "b_scan_display.h"
#include "ui_b_scan_display.h"

#include <QTimer>

#include "source/beams.h"
#include "scan_view.h"
#include "b_scan_scene.h"
#include "global.h"
#include "source/source.h"
#include "device/device.h"
#include "scroll_ruler_widget.h"
#include "b_scan_encoder_scene.h"
#include "b_scan_time_scene.h"
#include "fpga/fpga.h"


static const int SECOND         = 1000;

BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BscanDisplay),
    m_group(grp),
    m_bscanView(new ScanView),
    m_bscanScene(new BscanEncoderScene(DplDevice::Device::instance()->display()->palette(), grp->index())),
    m_type(ENCODER),
    m_currentBeamIndex(0),
    m_pixPerBeam(1.0),
    m_scanTypeRulerStart(0.0),
    m_scanTypeRulerEnd(0.0),
    m_soundPathRuler(NULL),
    m_scanTypeRuler(NULL),
    m_currentTimeCount(0.0),
    m_orientation(orientation)
{
    ui->setupUi(this);

    ui->colorBar->set_palette(DplDevice::Device::instance()->display()->palette());

    init_ruler();

    connect(m_bscanView, SIGNAL(size_changed(QSize)), this, SLOT(do_view_size_changed(QSize)));

    ui->bScanWidgetVerticalLayout->addWidget(m_bscanView);
    m_bscanView->setScene(m_bscanScene);

    connect(this, SIGNAL(update_ruler(double)), this, SLOT(do_update_ruler(double)));
    connect(this, SIGNAL(update_label(QString)), this, SLOT(do_update_label(QString)));

    /* source setting */
    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    ui->titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));

    DplFpga::Fpga::instance()->set_encoder_x_mode(DplFpga::Fpga::QUAD);
    DplFpga::Fpga::instance()->set_encoder_y_mode(DplFpga::Fpga::QUAD);

    if(m_orientation == Qt::Horizontal) {
        m_bscanView->rotate(-90);
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


bool BscanDisplay::set_scan_type(BscanDisplay::E_SCAN_TYPE type)
{
    if(m_type == type) {
        return true;
    }

    m_type = type;
    if(NULL != m_bscanScene) {
        delete m_bscanScene;
    }

    if(m_type == ENCODER) {
        m_bscanScene = new BscanEncoderScene(DplDevice::Device::instance()->display()->palette(), m_group->index());

    } else {
        m_bscanScene = new BscanTimeScene(DplDevice::Device::instance()->display()->palette(), m_group->index());
    }

    return true;
}

void BscanDisplay::init_ruler()
{
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
    if(m_bscanScene->width() == 0
            || m_bscanScene->height() == 0) {
        qDebug("[%s] w/h is 0.", __FUNCTION__);
        return;
    }

    if(beams.isNull()) {
        qDebug("[%s] beams is NULL.", __FUNCTION__);
        return;
    }

    if(m_type == TIME) {

        m_currentTimeCount += DplSource::Source::instance()->interval() / 1000.0;

        double rulerEnd;
        double stepTime =  (double)DplSource::Source::instance()->interval() / (double)SECOND;

        if(m_orientation == Qt::Horizontal) {

            rulerEnd = m_bscanView->height() / (SECOND / (double)DplSource::Source::instance()->interval());
            m_bscanScene->set_pix_per_beam(m_bscanScene->height() / (rulerEnd / stepTime));

        } else {

            rulerEnd = m_bscanView->width() / (SECOND / (double)DplSource::Source::instance()->interval());
            m_bscanScene->set_pix_per_beam(m_bscanScene->width() / (rulerEnd / stepTime));
        }

        m_bscanScene->set_beams(beams);

        if(m_currentTimeCount > rulerEnd) {
            m_bscanScene->set_scroll_window(true);
            emit update_ruler(m_currentTimeCount);
        }

        emit update_label(QString::number(m_currentTimeCount, 'f', 1));

    } else {

        double x = ((int)((beams->get(0)->encoder_x() / ENCODER_RESOLUTION + 0.005) * 100)) / 100.0; /* 保留小数点两位 */
        m_bscanScene->set_beams(beams);

        emit update_ruler(x);
    }
}

void BscanDisplay::do_update_ruler(double value)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    m_scanTypeRuler->move_to_value(value);
    m_scanTypeRuler->update();
}


void BscanDisplay::update_scan_type_ruler(const QSize &size)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    if(m_type == ENCODER) {
        /* 扫查轴 */
        /* 根据scan start/end 及resolution（扫查分辨率）计算待显示的总beam数 */
        double beamCount = (SCAN_END - SCAN_START) / SCAN_RESOLUTION;
        int width;
        if(m_orientation == Qt::Horizontal) {
            width = size.height();
        } else {
            width = size.width();
        }

        double pixCount;
        if(width >= beamCount) {
            /* 若显示区域大于beam数，则计算每条beam占多少pix */
            pixCount = width / beamCount;
            m_scanTypeRuler->set_range(SCAN_START, SCAN_END);
            m_bscanScene->set_pix_per_beam(pixCount);
            m_bscanScene->set_scroll_window(false);

        } else {
            /* 若显示区域小于beam数，则计算每条beam占一个pix */
            pixCount = MIN_PIX_COUNT;
            m_scanTypeRuler->set_range(SCAN_START, SCAN_START + width);
            m_bscanScene->set_pix_per_beam(pixCount);
            m_bscanScene->set_scroll_window(true);
        }

        qDebug() << "[" << __FUNCTION__ << "]" << " width = " << width
                 << " pixCount = " << pixCount
                 << " beamCount = " << beamCount;

    } else {

        m_scanTypeRulerStart = 0.0;
        double beamQtyPerSecond = SECOND / (double)DplSource::Source::instance()->interval();
        if(m_orientation == Qt::Horizontal) {
            m_scanTypeRulerEnd = size.height() / beamQtyPerSecond;
        } else {
            m_scanTypeRulerEnd = size.width() / beamQtyPerSecond;
        }

        m_scanTypeRuler->set_range(m_scanTypeRulerStart, m_scanTypeRulerEnd);
    }

    m_scanTypeRuler->update();
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
        start *= m_group->sample()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
        start /= 2;
        end   *= m_group->sample()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
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
    if (m_orientation == Qt::Horizontal) {

        m_bscanScene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                                   size.height(), size.width());
        m_bscanScene->set_size(QSize(size.height(), size.width()));

    } else {

        m_bscanScene->setSceneRect(-size.width()/2, -size.height()/2,
                                   size.width(), size.height());
        m_bscanScene->set_size(QSize(size.width(), size.height()));
    }

    update_scan_type_ruler(size);

}

