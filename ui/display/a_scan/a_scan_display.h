/**
 * @file a_scan_display.h
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_DISPLAY_H__
#define __A_SCAN_DISPLAY_H__

#include <device/device.h>

#include "../scan_display.h"

class ScanView;
class AscanScene;
class WaveItem;
class GateItem;
class TcgItem;

class AscanDisplay : public ScanDisplay
{
    Q_OBJECT
public:
    explicit AscanDisplay(const DplDevice::GroupPointer &group, QWidget *parent = 0);
    ~AscanDisplay();

protected slots:
    void do_size_changed(const QSize &size);
    void do_data_event();
    void update_gates();

protected:
    DplDevice::GroupPointer m_group;

    ScanView *m_view;
    AscanScene *m_scene;
    WaveItem *m_waveItem;
    GateItem *m_gateAItem;
    GateItem *m_gateBItem;
    GateItem *m_gateIItem;
    TcgItem *m_tcgItem;
};

#endif // __A_SCAN_DISPLAY_H__
