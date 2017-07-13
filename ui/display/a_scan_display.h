/**
 * @file a_scan_display.h
 * @brief A扫横向显示
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

class AscanView;
class AscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanDisplay(DplDevice::GroupPointer &group, AscanView *ascanWidget, QWidget *parent = 0);
    ~AscanDisplay();

protected slots:
    void do_data_event();

protected:
    Ui::AscanDisplay *ui;
    DplDevice::GroupPointer m_group;

private:
    AscanView *m_ascanWidget;
};

#endif // __A_SCAN_DISPLAY_H__
