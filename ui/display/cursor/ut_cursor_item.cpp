#include "ut_cursor_item.h"
#include "../../tool/tool.h"

#include <QGraphicsScene>

UtCursorItem::UtCursorItem(const DplDevice::GroupPointer &group,
                           Qt::Orientation orientation,
                           QColor color) :
    CursorItem(group->cursor(), orientation, color),
    m_group(group)
{
    connect(static_cast<DplUt::Sample *>(group->sample().data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_position()));
    connect(static_cast<DplUt::Sample *>(group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_position()));
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_background_color(DplDevice::Group::UtUnit)));
    update_background_color(group->ut_unit());
}

void UtCursorItem::set_text(double val)
{
    CursorItem::set_text(QString::number(Tool::cnf_to_display(m_group, val),'f', 2));
}

void UtCursorItem::update_background_color(DplDevice::Group::UtUnit unit)
{
    if (DplDevice::Group::Time == unit) {
        set_background_color(PalePinkColor);
    } else {
        set_background_color(PinkColor);
    }
}

double UtCursorItem::value() const
{
    if (orientation() == Qt::Horizontal) {
        return (scene()->sceneRect().bottom() - pos().y())
                / scene()->sceneRect().height()
                * group()->sample()->range()
                + group()->sample()->start();
    } else {
        return (pos().x() - scene()->sceneRect().left())
                / scene()->sceneRect().width()
                * group()->sample()->range()
                + group()->sample()->start();
    }
}
