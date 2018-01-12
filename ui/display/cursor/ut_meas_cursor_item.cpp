#include "ut_meas_cursor_item.h"
#include "../../tool/tool.h"

#include <QGraphicsView>

UtMeasCursorItem::UtMeasCursorItem(const DplDevice::GroupPointer &group,
                                   Qt::Orientation orientation) :
    UtCursorItem(group, orientation, Qt::darkGreen)
{
    connect(static_cast<DplMeasure::Cursor *>(group->cursor().data()),
            SIGNAL(ultrasound_measurement_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(group->cursor().data()),
            SIGNAL(ultrasound_measurement_changed(double)),
            this, SLOT(set_text(double)));
    set_text(cursor()->ultrasound_measurement());
}

void UtMeasCursorItem::position_event()
{
    if (!moving()) {
        return;
    }

    cursor()->set_ultrasound_measurement(value());
}

double UtMeasCursorItem::ratio() const
{
    return (cursor()->ultrasound_measurement() - group()->sample()->start())
            / group()->sample()->range();
}
