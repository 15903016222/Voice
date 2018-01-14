#ifndef __SCAN_CURSOR_ITEM_H__
#define __SCAN_CURSOR_ITEM_H__

#include "cursor_item.h"

#include <source/scan.h>

class ScanCursorItem : public CursorItem
{
    Q_OBJECT
public:
    ScanCursorItem(const DplMeasure::CursorPointer &cursor,
                   Qt::Orientation orientation,
                   QColor color);

    double visual_start() const;
    double visual_range() const;

public slots:
    void set_text(double val);
    void set_visual_range(double start, double range);

protected:
    double value() const;

private:
    DplSource::AxisPointer m_axis;
    double m_visualStart;
    double m_visualRange;
};

inline double ScanCursorItem::visual_start() const
{
    return m_visualStart;
}

inline double ScanCursorItem::visual_range() const
{
    return m_visualRange;
}

#endif // __SCAN_CURSOR_ITEM_H__
