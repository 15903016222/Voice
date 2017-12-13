/**
 * @file a_scan_display.cpp
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "a_scan_display.h"
#include "wave_item.h"
#include "gate_item.h"
#include "tcg_item.h"

#include "../base/scan_scene.h"
#include "../ruler/ruler.h"
#include "../color_bar/color_bar.h"

#include <global.h>

#include <QLabel>
#include <QThread>

AscanDisplay::AscanDisplay(const DplDevice::GroupPointer &group, QWidget *parent) :
    ScanDisplay(parent),
    m_group(group),
    m_waveItem(new WaveItem(DplDevice::Device::instance()->display()->ascan())),
    m_gateAItem(new GateItem(group->sample(), group->gate_a())),
    m_gateBItem(new GateItem(group->sample(), group->gate_b())),
    m_gateIItem(new GateItem(group->sample(), group->gate_i())),
    m_tcgItem(new TcgItem(group->tcgs(), group->sample()))
{  
    m_colorBar->hide();
    m_colorRuler->hide();

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
