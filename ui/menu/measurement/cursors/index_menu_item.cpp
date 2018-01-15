#include "index_menu_item.h"

#include <device/device.h>
#include <source/scan.h>
#include <float.h>

IndexMenuItem::IndexMenuItem(QWidget *parent, const QString &title) :
    CursorMenuItem(parent, title)
{
    set_decimals(1);
    set_step(0.1);
    set_unit("mm");

    DplSource::Axis *indexAxis = DplSource::Scan::instance()->index_axis().data();
    connect(indexAxis, SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(update_unit()));
    connect(indexAxis, SIGNAL(start_changed(float)),
            this, SLOT(update_range()));
    connect(indexAxis, SIGNAL(end_changed(float)),
            this, SLOT(update_range()));
}

void IndexMenuItem::update_unit()
{
    if (DplSource::Scan::instance()->index_axis()->driving()
            == DplSource::Axis::TIMER) {
        set_unit("s");
    } else {
        set_unit("mm");
    }
}

void IndexMenuItem::update_range()
{
    DplSource::AxisPointer axis = DplSource::Scan::instance()->index_axis();
    if (axis->driving() == DplSource::Axis::TIMER) {
        set_range(0, DBL_MAX);
    } else {
        set_range(axis->start(), axis->end());
    }
}
