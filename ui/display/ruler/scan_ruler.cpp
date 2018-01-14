#include "scan_ruler.h"

#include <source/source.h>
#include <source/scan.h>
#include <ut/global_transceiver.h>

ScanRuler::ScanRuler(const DplDevice::GroupPointer &grp, MarkPostion pos, QWidget *parent):
    Ruler(pos, "(mm)", parent),
    m_scan(DplSource::Scan::instance()),
    m_axis(m_scan->scan_axis()),
    m_group(grp)
{
    set_background_color(DarkBlueColor);
    set_pixel_per_mark(1);
    set_scroll(true);

    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    connect(DplUt::GlobalTransceiver::instance(),
            SIGNAL(prf_changed()),
            this, SLOT(update()));

    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update()));

    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(update()));

    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(resolution_changed(float)),
            this, SLOT(update()));

    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(update()));
}

double ScanRuler::start()
{
    if (mark_position() == Ruler::RIGHT) {
        return Ruler::stop();
    } else {
        return Ruler::start();
    }
}

double ScanRuler::stop()
{
    if (mark_position() == Ruler::RIGHT) {
        return Ruler::start();
    } else {
        return Ruler::stop();
    }
}

void ScanRuler::set_range(double start, double stop)
{
    if (mark_position() == Ruler::RIGHT) {
        Ruler::set_range(stop, start);
    } else {
        Ruler::set_range(start, stop);
    }
}

void ScanRuler::update()
{
    if (m_axis->driving() == DplSource::Axis::TIMER) {
        set_unit("(s)");
        set_range(0, range());
    } else {
        set_unit("(mm)");
        set_range(m_axis->start(), m_axis->start() + range());
        if ( stop() < m_axis->end() ) {
            set_scroll(true);
            set_pixel_per_mark(1);
        } else {
            set_scroll(false);
            set_pixel_per_mark(10);
        }
    }
    Ruler::update();
}

void ScanRuler::do_data_event(const DplSource::BeamsPointer &beams)
{
    double val = 0.0;

    if (m_axis->driving() == DplSource::Axis::TIMER) {
        val = DplSource::Source::instance()->elapsed();
    } else {
        if (m_axis->driving() == DplSource::Axis::ENCODER_X) {
            val = beams->get(0)->encoder_x();
        } else {
            val = beams->get(0)->encoder_y();
        }
        if (val < m_axis->start() || val > m_axis->end()) {
            return;
        }
    }

    if (val < start()) {
        set_range(val, val + range());
        emit start_changed(val, range());
    } else if (val > stop()) {
        set_range(val - range(), val);
        emit start_changed(val-range(), range());
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
        return 1.0*width() / DplSource::Source::instance()->acquisition_rate();
    } else {
        return 1.0*height() / DplSource::Source::instance()->acquisition_rate();
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
    update();
    emit start_changed(start(), range());
    Ruler::resizeEvent(e);
}
