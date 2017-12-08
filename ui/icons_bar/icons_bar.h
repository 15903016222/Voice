#ifndef __ICONS_BAR_H__
#define __ICONS_BAR_H__

#include "mcu/mcu.h"

#include <device/group.h>
#include <QWidget>

namespace Ui {
class IconsBar;
}

class IconsBar : public QWidget
{
    Q_OBJECT

public:
    explicit IconsBar(QWidget *parent = 0);
    ~IconsBar();

signals:
    void keyboard_event();

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);

    void do_temperature_event(Mcu::TemperatureType type, int value);
    void do_battery_status_event(int index, Mcu::BatteryStatus status);
    void do_battery_quantity_event(int index, int value);
    void do_driving_changed();

    void show_tcg(bool flag);
    void show_dac(bool flag);
    void show_sensitivity_calibration(bool flag);
    void show_velocity_calibration(bool flag);
    void show_delay_calibration(bool flag);

    void do_timeout();

private:
    Ui::IconsBar *ui;
    QTimer *m_timer;
    DplDevice::GroupPointer m_group;
};

#endif // __ICONS_BAR_H__
