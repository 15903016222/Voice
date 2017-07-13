#ifndef __A_SCAN_VWIDGET_H__
#define __A_SCAN_VWIDGET_H__

#include "a_scan_view.h"

class AscanVWidget : public AscanView
{
public:
    AscanVWidget(QWidget *parent = 0);

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
};

#endif // __A_SCAN_VWIDGET_H__
