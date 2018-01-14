#include "scan_cursor_item.h"

#include <QGraphicsScene>

ScanCursorItem::ScanCursorItem(const DplMeasure::CursorPointer &cursor,
                               Qt::Orientation orientation,
                               QColor color) :
    CursorItem(cursor, orientation, color, DarkBlueColor),
    m_axis(DplSource::Scan::instance()->scan_axis()),
    m_visualStart(m_axis->start()),
    m_visualRange(m_axis->end() - m_visualStart)
{
    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(update_position()));
    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_position()));
    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(update_position()));
    connect(static_cast<DplSource::Axis *>(m_axis.data()),
            SIGNAL(resolution_changed(float)),
            this, SLOT(update_position()));
}

void ScanCursorItem::set_text(double val)
{
    CursorItem::set_text(QString::number(val,'f', 2));
}

void ScanCursorItem::set_visual_range(double start, double range)
{
    m_visualStart = start;
    m_visualRange = range;
    update_position();
}

double ScanCursorItem::value() const
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
