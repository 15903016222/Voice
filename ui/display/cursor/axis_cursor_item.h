#ifndef __AXIS_CURSOR_ITEM_H__
#define __AXIS_CURSOR_ITEM_H__

#include "cursor_item.h"
#include <source/axis.h>

class AxisCursorItem : public CursorItem
{
    Q_OBJECT
public:
    AxisCursorItem(const DplMeasure::CursorPointer &cursor,
                   const DplSource::AxisPointer &axis,
                   Qt::Orientation orientation,
                   QColor color, QColor bgColor);

    double visual_start() const;
    double visual_range() const;

public slots:
    void set_visual_range(double start, double range);
    void set_text(double val);

protected:
    double value() const;

private:
    double m_visualStart;
    double m_visualRange;
};

inline double AxisCursorItem::visual_start() const
{
    return m_visualStart;
}

inline double AxisCursorItem::visual_range() const
{
    return m_visualRange;
}

#endif // __AXIS_CURSOR_ITEM_H__
