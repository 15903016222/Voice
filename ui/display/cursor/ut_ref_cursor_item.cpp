#include "ut_ref_cursor_item.h"
#include <QGraphicsView>

UtRefCursorItem::UtRefCursorItem(const DplDevice::GroupPointer &group,
                                   Qt::Orientation orientation) :
    UtCursorItem(group, orientation, Qt::darkRed)
{
    connect(static_cast<DplMeasure::Cursor *>(group->cursor().data()),
            SIGNAL(ultrasound_reference_changed(double)),
            this, SLOT(update_position()));
    connect(static_cast<DplMeasure::Cursor *>(group->cursor().data()),
            SIGNAL(ultrasound_reference_changed(double)),
            this, SLOT(set_text(double)));
    set_text(cursor()->ultrasound_reference());
}

void UtRefCursorItem::position_event()
{
    if (!moving()) {
        return;
    }
    cursor()->set_ultrasound_reference(value());
}

double UtRefCursorItem::ratio() const
{
    return (cursor()->ultrasound_reference() - group()->sample()->start())
            / group()->sample()->range();
}
