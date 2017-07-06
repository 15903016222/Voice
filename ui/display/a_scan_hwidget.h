/**
 * @file a_scan_hwidget.h
 * @brief A扫横向显示
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_HWIDGET_H__
#define __A_SCAN_HWIDGET_H__

#include "a_scan_widget.h"

class AscanHWidget : public AscanWidget
{
public:
    explicit AscanHWidget(QWidget *parent = 0);
    ~AscanHWidget();

protected:
    /**
     * @brief x_axis_length     获取X轴长度
     * @return                  长度(Pixel)
     */
    virtual int x_axis_length() const;

    /**
     * @brief y_axis_length     获取Y轴长度
     * @return                  长度(Pixel)
     */
    virtual int y_axis_length() const;

    void paintEvent(QPaintEvent *e);
};

#endif // __A_SCAN_HWIDGET_H__
