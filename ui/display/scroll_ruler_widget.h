#ifndef __SCROLL_RULER_WIDGET_H__
#define __SCROLL_RULER_WIDGET_H__

#include <QWidget>
#include <QResizeEvent>

#include "ui/display/ruler_widget.h"

class ScrollRulerWidget : public RulerWidget
{

public:

    explicit ScrollRulerWidget(QWidget *parent = 0);

    virtual bool set_range(double start, double end);

    /**
     * @brief move_to_value 将标尺移动到指定value，若value在当前标尺显示范围
     * 则不移动，若value大于end或小于start，则向start/end移动。
     * @param targetValue
     * @return
     */
    bool move_to_value(double targetValue);

    /**
     * @brief max_end 获取最大的标尺显示值
     * @return
     */
    inline double max_end() { return m_maxEnd;}

    /**
     * @brief set_max_end   设置标尺最大的标尺显示数值
     * @param maxEnd        最大数值
     * @return
     */
    bool set_max_end(double maxEnd);

    /**
     * @brief set_show_range    设置标尺显示的范围
     * @param start 标尺开始
     * @param end   标尺结束
     */
    void set_show_range(double start, double end);


protected:
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *event);

private:

    int     m_stepUnit;
    int     m_unitNum;
    int     m_offsetPix;
    double  m_moveTotalUnit;
    double  m_maxEnd;

    void init_step_unit();
};


#endif // __SCROLL_RULER_WIDGET_H__
