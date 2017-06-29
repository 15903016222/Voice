/**
 * @file a_scan_hdisplay.h
 * @brief A扫横向显示
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_HDISPLAY_H__
#define __A_SCAN_HDISPLAY_H__

#include <device/device.h>

#include <QWidget>

namespace Ui {
class AscanHDisplay;
}

class AscanHDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanHDisplay(DplDevice::GroupPointer &group, QWidget *parent = 0);
    ~AscanHDisplay();

protected slots:
    void update();

private:
    Ui::AscanHDisplay *ui;

    DplDevice::GroupPointer m_group;

private slots:
    void update_bottom_ruler();
};

#endif // __A_SCAN_DISPLAY_H__
