#include "status_bar.h"
#include "ui_status_bar.h"

#include <device/device.h>
#include <ut/global_pulser.h>
#include <source/scan.h>

#include <QTime>
#include <QTimer>
#include <ui/display/test_stub.h>

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar),
    m_timer(new QTimer),
    m_scan(DplSource::Scan::instance()),
    m_timeCount(0.0)
{
    ui->setupUi(this);
    ui->indexEncLabel->hide();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_timeout()));
    m_timer->start(1000);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_current_group_changed(DplDevice::GroupPointer)));

    connect(m_scan, SIGNAL(mode_changed(DplSource::Scan::Mode)),
            this, SLOT(do_scan_mode_changed(DplSource::Scan::Mode)));

     connect(this, SIGNAL(encoder_text_changed()),
            this, SLOT(do_encoder_text_changed()),
            Qt::QueuedConnection);

    do_current_group_changed(DplDevice::Device::instance()->current_group());

    ui->versionLabel->setText(DplDevice::Device::instance()->type_string() + " " + DplDevice::Device::instance()->version());

    connect(DplUt::GlobalPulser::instance(),
            SIGNAL(prf_changed()),
            this,
            SLOT(do_acquisition_rate_changed()));
    do_acquisition_rate_changed();
}

StatusBar::~StatusBar()
{
    delete m_timer;
    delete ui;
}

void StatusBar::do_timeout()
{
    ui->timeLabel->setText(QDateTime::currentDateTime().toString("MM-dd hh:mm:ss"));
}

void StatusBar::do_current_group_changed(const DplDevice::GroupPointer &grp)
{
    disconnect(static_cast<DplDevice::Group *>(grp.data()),
               SIGNAL(data_event(DplSource::BeamsPointer)),
               this, SLOT(do_data_event(DplSource::BeamsPointer)));

    m_group = grp;

    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);
}

void StatusBar::do_scan_mode_changed(DplSource::Scan::Mode mode)
{
    if (mode == DplSource::Scan::ONELINE) {
        ui->indexEncLabel->hide();
    } else {
        ui->indexEncLabel->show();
    }
}

void StatusBar::do_data_event(const DplSource::BeamsPointer &beams)
{
    QWriteLocker l(&m_encStringRWLock);

    m_scanEncStr = tr("Scan:");

    DplSource::AxisPointer scanAxis = m_scan->scan_axis();
    DplSource::AxisPointer indexAxis = m_scan->index_axis();
    DplSource::BeamPointer beam = beams->get(0);

    if (scanAxis->driving() == DplSource::Axis::TIMER) {
        m_scanEncStr += tr(" 0.0 s");
        m_timeCount = TestStub::instance()->get_time() + 0.02;
        TestStub::instance()->update_time(m_timeCount);
    } else if (scanAxis->driving() == DplSource::Axis::ENCODER_X) {
        m_scanEncStr += QString::number(beam->encoder_x()/ m_scan->encoder_x()->resolution(), 'f', 2) + " mm";
        m_timeCount = 0.0;
    } else {
        m_scanEncStr += QString::number(beam->encoder_y()/ m_scan->encoder_y()->resolution(), 'f', 2) + "mm";
        m_timeCount = 0.0;
    }

    if (indexAxis->driving() == DplSource::Axis::ENCODER_X) {
        m_indexEncStr = tr("Index:") + QString::number(beam->encoder_x()/m_scan->encoder_x()->resolution(), 'f', 2) + " mm";
    } else if (indexAxis->driving() == DplSource::Axis::ENCODER_Y) {
        m_indexEncStr = tr("Index:") + QString::number(beam->encoder_y()/m_scan->encoder_y()->resolution(), 'f', 2) + " mm";
    }

    emit encoder_text_changed();
}

void StatusBar::do_encoder_text_changed()
{
    QReadLocker l(&m_encStringRWLock);
    ui->scanEncLabel->setText(m_scanEncStr);
    ui->indexEncLabel->setText(m_indexEncStr);
}


void StatusBar::do_acquisition_rate_changed()
{
    ui->prfLabel->setText(QString("PRF:%1(%2)").arg(DplUt::GlobalPulser::instance()->acquisition_rate()).arg(DplUt::GlobalPulser::instance()->prf()));
}


