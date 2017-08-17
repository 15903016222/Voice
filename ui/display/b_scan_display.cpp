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

static const int TIME_OUT_VALUE = 20;
static const int SECOND         = 1000;

BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BscanDisplay),
    m_group(grp),
    m_bscanView(new ScanView),
    m_bscanScene(new BscanScene(DplDevice::Device::instance()->display()->palette())),
    m_type(TIME),
    m_currentBeamIndex(0),
    m_pixPerBeam(1.0),
    m_scanTypeRulerStart(0.0),
    m_scanTypeRulerEnd(0.0),
    m_soundPathRuler(NULL),
    m_scanTypeRuler(NULL),
    m_timer(new QTimer(this)),
    m_currentTimeCount(0.0)
{
    ui->setupUi(this);

    ui->colorBar->set_palette(DplDevice::Device::instance()->display()->palette());

    init_ruler();

    /* source setting */
    DplSource::BeamsPointer beams = m_group->beams();

    connect(static_cast<DplSource::Beams *>(beams.data()),
            SIGNAL(data_event()),
            this,
            SLOT(do_data_event()));

    ui->titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));

    connect(m_bscanView, SIGNAL(size_changed(QSize)), m_bscanScene, SLOT(set_size(QSize)));
    connect(m_bscanView, SIGNAL(size_changed(QSize)), this, SLOT(update_scan_type_ruler(QSize)));

    ui->bScanWidgetVerticalLayout->addWidget(m_bscanView);
    m_bscanView->setScene(m_bscanScene);

    connect(m_bscanScene, SIGNAL(one_beam_show_successed()), this, SLOT(update_scan_type_ruler()));

    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_timer_time_outed()));
//    m_timer->start(TIME_OUT_VALUE);

}

BscanDisplay::~BscanDisplay()
{
    delete ui;

    delete m_bscanScene;
    delete m_bscanView;
}

bool BscanDisplay::set_current_beam(unsigned int index)
{
    if(m_group->beams()->beam_qty() == 0) {
        return false;
    }

    if(index < m_group->beams()->beam_qty()) {
        m_currentBeamIndex = index;
        return true;
    }

    return false;
}


bool BscanDisplay::set_scan_type(BscanDisplay::E_SCAN_TYPE type)
{
    if(m_type == type) {
        return true;
    }
    m_type = type;

//    if(m_bscanScene != NULL) {
//        if(m_type == TIME) {
//            m_bscanScene = new BscanScene(DplDevice::Device::instance()->display()->palette());
//        } else if(m_type == ENCODER) {
//            m_bscanScene->set_direction(BscanScene::HORIZONTAL);
//        } else {
//            m_bscanScene = NULL;
//            return false;
//        }

//    }
//    delete m_bscanScene;

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


void BscanDisplay::do_data_event()
{
    m_currentTimeCount += TIME_OUT_VALUE / 1000.0;
    ui->label->setText(QString::number(m_currentTimeCount, 'f', 1));

    double rulerEnd;
    double stepTime =  (double)DplSource::Source::instance()->interval() / (double)SECOND;

    if(m_bscanScene->direction() == BscanScene::HORIZONTAL) {

        rulerEnd = m_bscanView->height() / (SECOND / (double)DplSource::Source::instance()->interval());
        m_bscanScene->set_pix_per_beam(m_bscanScene->height() / (rulerEnd / stepTime));

    } else {

        rulerEnd = m_bscanView->width() / (SECOND / (double)DplSource::Source::instance()->interval());
        m_bscanScene->set_pix_per_beam(m_bscanScene->width() / (rulerEnd / stepTime));
    }

    if(m_currentTimeCount > rulerEnd) {

//        if(m_currentTimeCount > 5 * rulerEnd) {
//            DplSource::BeamsPointer beams = m_group->beams();
//            disconnect(static_cast<DplSource::Beams *>(beams.data()),
//                    SIGNAL(data_event()),
//                    this,
//                    SLOT(do_data_event()));
//            return;
//        }

        m_scanTypeRuler->move_unit(TIME_OUT_VALUE);
        m_scanTypeRuler->update();
    }

    m_bscanScene->show_wave(m_group->beams()->get(m_currentBeamIndex));

//    if(rulerEnd - m_currentTimeCount < 0.0000000001 && rulerEnd - m_currentTimeCount >= -0.0000000001) {
//        DplSource::BeamsPointer beams = m_group->beams();
//        disconnect(static_cast<DplSource::Beams *>(beams.data()),
//                   SIGNAL(data_event()),
//                   this,
//                   SLOT(do_data_event()));
//        return;
//    }
}


void BscanDisplay::update_scan_type_ruler(const QSize &size)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    m_scanTypeRulerStart = 0.0;
    double beamQtyPerSecond = SECOND / (double)DplSource::Source::instance()->interval();
    if(m_bscanScene->direction() == BscanScene::HORIZONTAL) {
        m_scanTypeRulerEnd   = size.height() / beamQtyPerSecond;
    } else {
        m_scanTypeRulerEnd   = size.width() / beamQtyPerSecond;
    }
    m_scanTypeRuler->set_range(m_scanTypeRulerStart, m_scanTypeRulerEnd);
    m_scanTypeRuler->update();

}


void BscanDisplay::update_scan_type_ruler()
{
    /* 编码器扫查时，当x超过ruler的range时，更新ruler */
    /* 编码器参数有：1.扫查起点。2.扫查终点。扫查分辨率。*/

//    if(m_scanTypeRuler == NULL) {
//        return;
//    }

//    m_scanTypeRulerStart += DplSource::Source::instance()->interval();
//    m_scanTypeRulerEnd   += DplSource::Source::instance()->interval();
//    m_scanTypeRuler->set_range(m_scanTypeRulerStart, m_scanTypeRulerEnd);
//    m_scanTypeRuler->update();
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

void BscanDisplay::do_timer_time_outed()
{
    m_currentTimeCount += TIME_OUT_VALUE / 1000.0;
    ui->label->setText(QString::number(m_currentTimeCount, 'f', 1));

    m_bscanScene->show_wave(m_group->beams()->get(m_currentBeamIndex));

    if(m_currentTimeCount > (SECOND / (double)DplSource::Source::instance()->interval())) {

        static int timeOutedCount = 0;

        m_scanTypeRulerStart += 0.02;
        m_scanTypeRulerEnd   += 0.02;
        ++timeOutedCount;

        if(timeOutedCount == 5){
            m_scanTypeRuler->set_range(m_scanTypeRulerStart, m_scanTypeRulerEnd);
            m_scanTypeRuler->update();
            timeOutedCount = 0;
        }
    }
}




