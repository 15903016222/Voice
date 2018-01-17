#ifndef __AMP_CURSOR_ITEM_H__
#define __AMP_CURSOR_ITEM_H__

#include "cursor_item.h"

class AmpCursorItem : public CursorItem
{
    Q_OBJECT
public:
    AmpCursorItem(const DplMeasure::CursorPointer &cursor,
                  Qt::Orientation orientation,
                  QColor color);

public slots:
    void set_text(double val);

protected:
    double value() const;
};

#endif // __AMP_CURSOR_ITEM_H__
