#ifndef __SCROLL_RULER_WIDGET_H__
#define __SCROLL_RULER_WIDGET_H__

#include <QWidget>

#include "ui/display/ruler_widget.h"

class ScrollRulerWidget : public RulerWidget
{
    Q_OBJECT
public:

    explicit ScrollRulerWidget(QWidget *parent = 0);

    void move_unit(unsigned int msec);
    void move_encoder_x(unsigned int step);

protected:
    virtual void paintEvent(QPaintEvent *e);

private:

    int     m_stepUnit;
    int     m_unitNum;
    int     m_offsetPix;
    double  m_moveTotalUnit;
};


#endif // __SCROLL_RULER_WIDGET_H__
