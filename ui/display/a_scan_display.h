/**
 * @file a_scan_display.h
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_DISPLAY_H__
#define __A_SCAN_DISPLAY_H__

#include <device/device.h>

#include <QWidget>

namespace Ui {
class AscanDisplay;
}

class ScanView;
class AscanScene;
class WaveItem;
class GateItem;

class AscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanDisplay(const DplDevice::GroupPointer &group,
                          Qt::Orientation orientation, QWidget *parent = 0);
    ~AscanDisplay();

protected slots:
    void do_data_event();
    void do_view_size_changed(const QSize &size);
    void update_gates();

protected:
    Ui::AscanDisplay *ui;
    DplDevice::GroupPointer m_group;

private:
    ScanView *m_view;
    AscanScene *m_scene;
    WaveItem *m_waveItem;
    GateItem *m_gateAItem;
    GateItem *m_gateBItem;
    GateItem *m_gateIItem;
    Qt::Orientation m_orientation;
};

#endif // __A_SCAN_DISPLAY_H__
