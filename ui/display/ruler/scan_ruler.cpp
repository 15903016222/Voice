#include "scan_ruler.h"

#include <source/source.h>
#include <source/scan.h>

ScanRuler::ScanRuler(const DplDevice::GroupPointer &grp, MarkPostion pos, QWidget *parent):
    Ruler(pos, "(mm)", parent),
    m_scan(DplSource::Scan::instance()),
    m_axis(m_scan->scan_axis()),
    m_group(grp)
{
    set_background_color(DarkBlueColor);
    set_scroll(true);

    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this,
            SLOT(do_driving_changed(DplSource::Axis::Driving)));
    do_driving_changed(m_axis->driving());
}

void ScanRuler::do_data_event(const DplSource::BeamsPointer &beams)
{
    double val = 0.0;

    if (m_axis->driving() == DplSource::Axis::TIMER) {
        val = DplSource::Source::instance()->elapsed();
    } else {
        if (m_axis->driving() == DplSource::Axis::ENCODER_X) {
            val = beams->get(0)->encoder_x() / m_scan->encoder_x()->resolution();
        } else {
            val = beams->get(0)->encoder_y() / m_scan->encoder_y()->resolution();
        }

        if (val < m_axis->start() || val > m_axis->end()) {
            return;
        }
    }

    if (val < start()) {
        set_range(val, val + range());
    } else if (val > stop()) {
        set_range(val - range(), val);
    }
}

void ScanRuler::do_driving_changed(DplSource::Axis::Driving driving)
{
    if (driving == DplSource::Axis::TIMER) {
        set_unit("(s)");
        set_range(0, range());
    } else {
        set_unit("(mm)");
        set_range(m_axis->start(), m_axis->start() + range());
    }
}

double ScanRuler::range() const
{
    if (m_axis->driving() == DplSource::Axis::TIMER) {
        return time_range();
    } else {
        return encoder_range();
    }
}

double ScanRuler::time_range() const
{
    if (mark_position() == TOP || mark_position() == BOTTOM) {
        return width() / DplSource::Source::instance()->prf();
    } else {
        return height() / DplSource::Source::instance()->prf();
    }
}

double ScanRuler::encoder_range() const
{
    double range = (m_axis->end() - m_axis->start()) / m_axis->resolution();

    if (mark_position() == TOP || mark_position() == BOTTOM) {
        if (range > width()) {
            range = width();
        }
    } else {
        if (range > height()) {
            range = height();
        }
    }
    return range * m_axis->resolution();
}

void ScanRuler::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    if (m_axis->driving() == DplSource::Axis::TIMER) {
        set_unit("(s)");
        set_range(0, range());
    } else {
        set_unit("(mm)");
        set_range(m_axis->start(), range());
    }

    if (start() + range() > stop()) {
        set_range(stop()-range(), stop());
    } else {
        set_range(start(), range());
    }
}
