/**
 * @file a_scan_display.cpp
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "a_scan_display.h"
#include "a_scan_scene.h"
#include "wave_item.h"
#include "gate_item.h"
#include "tcg_item.h"

#include "../scan_view.h"
#include "../color_bar.h"
#include "../ruler/ruler.h"

#include <global.h>

#include <QThread>
#include <QLayout>
#include <QLabel>

AscanDisplay::AscanDisplay(const DplDevice::GroupPointer &group, QWidget *parent) :
    ScanDisplay(parent),
    m_group(group),
    m_view(new ScanView),
    m_scene(new AscanScene),
    m_waveItem(new WaveItem(DplDevice::Device::instance()->display()->ascan())),
    m_gateAItem(new GateItem(group->sample(), group->gate_a())),
    m_gateBItem(new GateItem(group->sample(), group->gate_b())),
    m_gateIItem(new GateItem(group->sample(), group->gate_i())),
    m_tcgItem(new TcgItem(group->tcgs(), group->sample()))
{  
    m_rightRuler->hide();
    m_colorBar->hide();

    init_amplitude_ruler();
    init_ultrasound_ruler();

    m_view->setScene(m_scene);

    m_scene->addItem(m_waveItem);

    m_scene->addItem(m_gateAItem);
    m_scene->addItem(m_gateBItem);
    m_scene->addItem(m_gateIItem);

    m_scene->addItem(m_tcgItem);


    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_gates()));

    /* source setting */    
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event()),
            Qt::DirectConnection);

    m_titleLabel->setText(QString("A-Scan|Grp")+QString::number(m_group->index()+1));
}

AscanDisplay::~AscanDisplay()
{
    delete m_view;
    delete m_scene;
}

void AscanDisplay::init_amplitude_ruler()
{
    Ruler *r = amplitude_ruler();

    if (r == m_leftRuler) {
        r->set_range(0, 100);
    } else if (r == m_bottomRuler){
        r->set_range(100, 0);
    }

    r->set_prec(0);
    r->set_unit("(%)");
    r->set_background_color(Qt::yellow);
}

void AscanDisplay::init_ultrasound_ruler()
{
    Ruler *r = ultrasound_ruler();

    r->set_scroll(true);

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_ultrasound_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_ultrasound_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_ultrasound_ruler()));
    update_ultrasound_ruler();
}

void AscanDisplay::do_data_event()
{
    DplSource::BeamPointer beam = m_group->current_beam();
    m_waveItem->set_wave(beam->wave(), !m_group->transceiver()->rectifier());

    if (m_gateAItem->isVisible()) {
        if (m_group->gate_a()->synchro_mode() == DplFpga::Group::SYNCHRO_I) {
            m_gateAItem->set_offset(beam->gate_peak_position(DplSource::Beam::GATE_I) * DplFpga::Fpga::SAMPLE_PRECISION);
        } else {
            m_gateAItem->set_offset(0);
        }
    }

    if (m_gateBItem->isVisible()) {
        if (m_group->gate_b()->synchro_mode() == DplFpga::Group::SYNCHRO_I) {
            m_gateBItem->set_offset(beam->gate_peak_position(DplSource::Beam::GATE_I) * DplFpga::Fpga::SAMPLE_PRECISION);
        } else if(m_group->gate_b()->synchro_mode() == DplFpga::Group::SYNCHRO_A) {
            m_gateBItem->set_offset(beam->gate_peak_position(DplSource::Beam::GATE_A) * DplFpga::Fpga::SAMPLE_PRECISION);
        } else {
            m_gateBItem->set_offset(0);
        }
    }
}

void AscanDisplay::resize_event(const QSize &size)
{
    Q_UNUSED(size);
    update_gates();
}

void AscanDisplay::update_gates()
{
    m_gateAItem->set_ratio(m_scene->width()/m_group->sample()->range());
    m_gateBItem->set_ratio(m_scene->width()/m_group->sample()->range());
    m_gateIItem->set_ratio(m_scene->width()/m_group->sample()->range());
}

void AscanDisplay::update_ultrasound_ruler()
{
    double start = m_group->sample()->start();
    double end = (start + m_group->sample()->range());

    start = Dpl::ns_to_us(start);
    end = Dpl::ns_to_us(end);

    DplDevice::Group::UtUnit unit = m_group->ut_unit();
    Ruler *r = ultrasound_ruler();

    if (DplDevice::Group::Time == unit) {
        r->set_unit("(us)");
        r->set_background_color(QColor("#F7C8CF"));
    } else {
        r->set_unit("(mm)");
        start *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        start /= 2;
        end *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        end /= 2;
        r->set_background_color(QColor("#FFC0CB"));
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            r->set_background_color(QColor("#A020F0"));
        }
    }

    r->set_range(start, end);
}

