#ifndef __V_DISPLAY_CURSOR_ITEM_H__
#define __V_DISPLAY_CURSOR_ITEM_H__

#include "../base_cursor_item.h"

class VDisplayCursorItem : public BaseCursorItem
{
public:
    explicit VDisplayCursorItem(Qt::Orientation cursorOrientation,
                    E_CURSOR_TYPE cursorType,
                    QGraphicsItem *parent = 0);

protected:
    /**
     * @brief paint_cursor  画光标
     * @param painter       画光标的painter
     */
    virtual void paint_cursor(QPainter *painter);

};

#endif // __V_DISPLAY_CURSOR_ITEM_H__
