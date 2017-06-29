#ifndef __A_SCAN_VDISPLAY_H__
#define __A_SCAN_VDISPLAY_H__

#include <device/device.h>

#include <QWidget>

namespace Ui {
class AscanVDisplay;
}

class AscanVDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit AscanVDisplay(DplDevice::GroupPointer &group, QWidget *parent = 0);
    ~AscanVDisplay();

protected slots:
    void update();

private:
    Ui::AscanVDisplay *ui;

    DplDevice::GroupPointer m_group;

private slots:
    void update_left_ruler();
};

#endif // __A_SCAN_DISPLAY_H__
