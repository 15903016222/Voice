/**
 * @file a_scan_display.h
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_DISPLAY_H__
#define __A_SCAN_DISPLAY_H__

#include <device/device.h>

#include "../base/scan_display.h"

class ScanView;
class ScanScene;
class WaveItem;
class GateItem;
class TcgItem;

class AscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit AscanDisplay(const DplDevice::GroupPointer &group, QWidget *parent = 0);
    ~AscanDisplay();

protected:
    virtual Ruler *amplitude_ruler() const = 0;
    virtual Ruler *ultrasound_ruler() const = 0;

    void init_amplitude_ruler();
    void init_ultrasound_ruler();

protected slots:
    void resize_event(const QSize &size);

    void do_data_event();
    void update_gates();
    void update_ultrasound_ruler();

protected:
    DplDevice::GroupPointer m_group;

    WaveItem *m_waveItem;
    GateItem *m_gateAItem;
    GateItem *m_gateBItem;
    GateItem *m_gateIItem;
    TcgItem *m_tcgItem;
};

#endif // __A_SCAN_DISPLAY_H__
