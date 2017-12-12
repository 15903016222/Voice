/**
 * @file a_scan_display.cpp
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "global.h"
#include "a_scan_display.h"

#include "../scan_view.h"
#include "../color_bar.h"
#include "../ruler/ruler.h"

#include "a_scan_scene.h"
#include "wave_item.h"
#include "gate_item.h"
#include "tcg_item.h"

#include <qmath.h>
#include <QThread>
#include <QLayout>
#include <QLabel>

AscanDisplay::AscanDisplay(const DplDevice::GroupPointer &group,
                           Qt::Orientation orientation, QWidget *parent) :
    ScanDisplay(parent),
    m_group(group),
    m_view(new ScanView),
    m_scene(new AscanScene),
    m_waveItem(new WaveItem(DplDevice::Device::instance()->display()->ascan())),
    m_gateAItem(new GateItem(group->sample(), group->gate_a())),
    m_gateBItem(new GateItem(group->sample(), group->gate_b())),
    m_gateIItem(new GateItem(group->sample(), group->gate_i())),
    m_tcgItem(new TcgItem(group->tcgs(), group->sample())),
    m_orientation(orientation)
{  
    m_rightRuler->hide();
    m_colorBar->hide();

    m_scanLayout->addWidget(m_view);

    connect(m_view, SIGNAL(size_changed(QSize)),
            this, SLOT(do_view_size_changed(QSize)));

    m_view->setScene(m_scene);

    m_scene->addItem(m_waveItem);

    m_scene->addItem(m_gateAItem);
    m_scene->addItem(m_gateBItem);
    m_scene->addItem(m_gateIItem);

    m_scene->addItem(m_tcgItem);

    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_gates()));

    if (orientation == Qt::Vertical) {
        m_view->rotate(90);
    }

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

void AscanDisplay::do_view_size_changed(const QSize &size)
{
    if (m_orientation == Qt::Horizontal) {
        m_scene->setSceneRect(-size.width()/2, -size.height()/2,
                                   size.width(), size.height());
        m_waveItem->set_size(size);
        m_tcgItem->set_size(size);
    } else {
        m_scene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                                   size.height(), size.width());
        m_waveItem->set_size(QSize(size.height(), size.width()));
        m_tcgItem->set_size(QSize(size.height(), size.width()));
    }

    update_gates();
}

void AscanDisplay::update_gates()
{
    m_gateAItem->set_ratio(m_scene->width()/m_group->sample()->range());
    m_gateBItem->set_ratio(m_scene->width()/m_group->sample()->range());
    m_gateIItem->set_ratio(m_scene->width()/m_group->sample()->range());
}

