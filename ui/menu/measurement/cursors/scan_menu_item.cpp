#include "scan_menu_item.h"

#include <device/device.h>
#include <source/scan.h>
#include <float.h>

ScanMenuItem::ScanMenuItem(QWidget *parent, const QString &title) :
    CursorMenuItem(parent, title)
{
    set_decimals(1);
    set_step(0.1);

    DplSource::Axis *scanAxis = DplSource::Scan::instance()->scan_axis().data();
    connect(scanAxis, SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(update_unit()));
    connect(scanAxis, SIGNAL(start_changed(float)),
            this, SLOT(update_range()));
    connect(scanAxis, SIGNAL(end_changed(float)),
            this, SLOT(update_range()));
}

void ScanMenuItem::update_unit()
{
    if (DplSource::Scan::instance()->scan_axis()->driving()
            == DplSource::Axis::TIMER) {
        set_unit("s");
    } else {
        set_unit("mm");
    }
}

void ScanMenuItem::update_range()
{
    DplSource::AxisPointer axis = DplSource::Scan::instance()->scan_axis();
    if (axis->driving() == DplSource::Axis::TIMER) {
        set_range(0, DBL_MAX);
    } else {
        set_range(axis->start(), axis->end());
    }
}
