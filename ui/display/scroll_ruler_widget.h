#ifndef __SCROLL_RULER_WIDGET_H__
#define __SCROLL_RULER_WIDGET_H__

#include <QWidget>
#include <QResizeEvent>

#include "ui/display/ruler_widget.h"

class ScrollRulerWidget : public RulerWidget
{
    Q_OBJECT
public:

    explicit ScrollRulerWidget(QWidget *parent = 0);

    void move_to_value(double targetValue);

protected:
    virtual void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *event);

private:

    int     m_stepUnit;
    int     m_unitNum;
    int     m_offsetPix;
    double  m_moveTotalUnit;
};


#endif // __SCROLL_RULER_WIDGET_H__
