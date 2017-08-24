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

static const int SECOND         = 1000;

BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BscanDisplay),
    m_group(grp),
    m_bscanView(new ScanView),
    m_bscanScene(new BscanTimeScene(DplDevice::Device::instance()->display()->palette(), grp->index())),
    m_type(TIME),
    m_currentBeamIndex(0),
    m_pixPerBeam(1.0),
    m_scanTypeRulerStart(0.0),
    m_scanTypeRulerEnd(0.0),
    m_soundPathRuler(NULL),
    m_scanTypeRuler(NULL),
    m_currentTimeCount(0.0)
{
    ui->setupUi(this);

    ui->colorBar->set_palette(DplDevice::Device::instance()->display()->palette());

    init_ruler();

    /* source setting */
    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    ui->titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));

    connect(m_bscanView, SIGNAL(size_changed(QSize)), m_bscanScene, SLOT(set_size(QSize)));
    connect(m_bscanView, SIGNAL(size_changed(QSize)), this, SLOT(update_scan_type_ruler(QSize)));

    ui->bScanWidgetVerticalLayout->addWidget(m_bscanView);
    m_bscanView->setScene(m_bscanScene);

    connect(m_bscanScene, SIGNAL(one_beam_show_successed()), this, SLOT(update_scan_type_ruler()));
    connect(this, SIGNAL(update_ruler()), this, SLOT(do_update_ruler()));

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

#if 0
    DplSource::BeamsPointer tmp1 = beams;
    qDebug() << "[" << __FUNCTION__ << "]" << " index = " << tmp1->get(0)->index();
    return;

#else
    DplSource::BeamsPointer tmp = beams;

    for(int i = 0; i < tmp->get(0)->index(); ++i) {
        DplSource::BeamsPointer check = DplSource::Source::instance()->beams(m_group->index(), tmp->get(0)->index() - i);
        if(check.isNull()) {
            qDebug() << "[" << __FUNCTION__ << "]" << " check is NULL"
                     << " target index = " << tmp->get(0)->index() - i << " index = " << tmp->get(0)->index();
        }
    }

#endif

    qDebug() << "[" << __FUNCTION__ << "]" << "======================";
    return;

    m_currentTimeCount += DplSource::Source::instance()->interval() / 1000.0;
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

    m_bscanScene->show_wave(beams);

    if(m_currentTimeCount > rulerEnd) {
        emit update_ruler();
    }

}

void BscanDisplay::do_update_ruler()
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    m_scanTypeRuler->move_unit(DplSource::Source::instance()->interval());
    m_scanTypeRuler->update();
}


void BscanDisplay::update_scan_type_ruler(const QSize &size)
{
    if(m_scanTypeRuler == NULL) {
        return;
    }

    m_scanTypeRulerStart = 0.0;
    double beamQtyPerSecond = SECOND / (double)DplSource::Source::instance()->interval();
    if(m_bscanScene->direction() == BscanScene::HORIZONTAL) {
        m_scanTypeRulerEnd = size.height() / beamQtyPerSecond;
    } else {
        m_scanTypeRulerEnd = size.width() / beamQtyPerSecond;
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

