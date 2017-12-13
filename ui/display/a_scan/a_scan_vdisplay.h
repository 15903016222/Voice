/**
 * @file a_scan_vdisplay.h
 * @brief A扫纵向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#ifndef __A_SCAN_VDISPLAY_H__
#define __A_SCAN_VDISPLAY_H__

#include "a_scan_display.h"

class AscanVDisplay : public AscanDisplay
{
    Q_OBJECT
public:
    explicit AscanVDisplay(const DplDevice::GroupPointer &group,
                           QWidget *parent = 0);
protected:
    Ruler *amplitude_ruler() const;
    Ruler *ultrasound_ruler() const;

protected slots:
    void resize_event(const QSize &size);
};

#endif // __A_SCAN_DISPLAY_H__
