/**
 * @file s_scan.cpp
 * @brief S-Scan信息类
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-11-10
 */
#include "s_scan.h"

namespace DplDisplay {

Sscan::Sscan(const DplFocallaw::FocallawerPointer &focallawer,
             const DplUt::SamplePointer &sample) : QObject(),
    m_startX(0),
    m_stopX(0),
    m_startY(0),
    m_stopY(0),
    m_focallawer(focallawer),
    m_sample(sample)
{
    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(focallawed()),
            this, SLOT(update_xy()));
    connect(static_cast<DplUt::Sample *>(m_sample.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_xy()));
    connect(static_cast<DplUt::Sample *>(m_sample.data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_xy()));
    update_xy();
}

void Sscan::update_xy()
{
    if (!m_focallawer->probe()->is_pa()) {
        return;
    }

    DplFocallaw::PaProbePointer probe = m_focallawer->probe().staticCast<DplFocallaw::PaProbe>();
    QList<DplFocallaw::BeamPointer> beams = m_focallawer->beams();
    float fstInPoint = beams.first()->field_distance();
    float lstInPoint = beams.last()->field_distance();

    if (probe->scan_configure()->mode() == DplFocallaw::ScanCnf::Linear) {
        m_startX = fstInPoint;
        m_stopX = lstInPoint;
        m_startY = m_sample->start();
        m_stopY = m_startY + m_sample->range();
    } else {
        DplFocallaw::SectorialScanCnfPointer scanCnf = probe->scan_configure().staticCast<DplFocallaw::SectorialScanCnf>();
        float angleStart = Dpl::degree2pi(scanCnf->first_angle());
        float angleStop = Dpl::degree2pi(scanCnf->last_angle());
        float sampleStop = m_sample->start() + m_sample->range();
        if (angleStart * angleStop <= 0) {
            m_startX = fstInPoint + sampleStop * qSin(angleStart);
            m_stopX  = lstInPoint + sampleStop * qSin(angleStop);
            m_stopY  = sampleStop;
            if (qFabs(angleStart) > qFabs(angleStop)) {
                m_startY = m_sample->start() * qCos(angleStart);
            } else {
                m_startY = m_sample->start() * qCos(angleStop);
            }
        } else if( angleStart < 0 && angleStop < 0) {
            m_startX = fstInPoint + sampleStop * qSin(angleStart);
            m_stopX  = lstInPoint + m_sample->start() * qSin(angleStop);
            m_startY = m_sample->start() * qCos(angleStart);
            m_stopY  = sampleStop * qCos(angleStop);
        } else { //( _nAngleStart > 0 && _nAngleStop > 0)
            m_startX = fstInPoint + m_sample->start() * qSin(angleStart) ;
            m_stopX  = lstInPoint + sampleStop * qSin(angleStop);
            m_startY = m_sample->start() * qCos(angleStop);
            m_stopY  = sampleStop * qCos(angleStart);
        }
    }

    emit xy_changed();
}

}
