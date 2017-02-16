#ifndef __MODE_LIST_WIDGET_ITEM_H__
#define __MODE_LIST_WIDGET_ITEM_H__

#include <QListWidgetItem>
#include <display.h>

class ModeListWidgetItem : public QListWidgetItem
{
public:
    static const int W_SIZE;
    static const int H_SIZE;

    ModeListWidgetItem(DplDisplay::Display::Mode mode);

    DplDisplay::Display::Mode get_mode() const { return m_mode; }

private:
    DplDisplay::Display::Mode m_mode;
};

#endif // __MODE_LIST_WIDGET_ITEM_H__
