#include "axis_cursor_item.h"

#include <QGraphicsScene>

AxisCursorItem::AxisCursorItem(const DplMeasure::CursorPointer &cursor,
                               const DplSource::AxisPointer &axis,
                               Qt::Orientation orientation,
                               QColor color,
                               QColor bgColor) :
    CursorItem(cursor, orientation, color, bgColor),
    m_visualStart(axis->start()),
    m_visualRange(axis->end() - m_visualStart)
{
    connect(static_cast<DplSource::Axis *>(axis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(update_position()));
    connect(static_cast<DplSource::Axis *>(axis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_position()));
    connect(static_cast<DplSource::Axis *>(axis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(update_position()));
    connect(static_cast<DplSource::Axis *>(axis.data()),
            SIGNAL(resolution_changed(float)),
            this, SLOT(update_position()));
}

void AxisCursorItem::set_visual_range(double start, double range)
{
    m_visualStart = start;
    m_visualRange = range;
    update_position();
}

void AxisCursorItem::set_text(double val)
{
    CursorItem::set_text(QString::number(val,'f', 2));
}

double AxisCursorItem::value() const
{
    if (orientation() == Qt::Horizontal) {
        return (scene()->sceneRect().bottom() - pos().y())
                / scene()->sceneRect().height()
                * m_visualRange + m_visualStart;
    } else {
        return (pos().x() -  scene()->sceneRect().left())
                / scene()->sceneRect().width()
                * m_visualRange + m_visualStart;
    }
}
