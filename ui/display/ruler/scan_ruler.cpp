#include "scan_ruler.h"

#include <source/source.h>
#include <source/scan.h>

ScanRuler::ScanRuler(const DplDevice::GroupPointer &grp, MarkPostion pos, QWidget *parent):
    Ruler(pos, "(mm)", parent),
    m_scan(DplSource::Scan::instance()),
    m_axis(m_scan->scan_axis()),
    m_group(grp)
{
    set_scroll(true);
    set_range(0, range());
    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);
}

void ScanRuler::do_data_event(const DplSource::BeamsPointer &beams)
{
    double val = 0.0;

    if (m_axis->driving() == DplSource::Axis::TIMER) {
        val = DplSource::Source::instance()->elapsed();
        set_unit("(s)");
    } else if (m_axis->driving() == DplSource::Axis::ENCODER_X) {
        val = beams->get(0)->encoder_x() / m_scan->encoder_x()->resolution();
        set_unit("(mm)");
    } else {
        val = beams->get(0)->encoder_y() / m_scan->encoder_y()->resolution();
        set_unit("(mm)");
    }

    if (val < start()) {
        set_range(val, val + range());
    } else if (val > stop()) {
        set_range(val - range(), val);
    }
}

double ScanRuler::range() const
{
    double range = m_axis->end() - m_axis->start();
    if (m_axis->driving() == DplSource::Axis::TIMER) {
        range /= m_scan->speed();
    } else if (m_axis->driving() == DplSource::Axis::ENCODER_X) {
        range /= m_scan->encoder_x()->resolution();
    } else {
        range /= m_scan->encoder_y()->resolution();
    }

    if (mark_position() == TOP || mark_position() == BOTTOM) {
        if (range > width()) {
            range = width();
        }
    } else {
        if (range > height()) {
            range = height();
        }
    }
    return range;
}
