#ifndef __ICONS_BAR_H__
#define __ICONS_BAR_H__

#include "mcu.h"

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

public slots:
    void do_temperature_event(Mcu::TemperatureType type, int value);
    void do_battery_status_event(int index, Mcu::BatteryStatus status);
    void do_battery_quantity_event(int index, int value);

    void show_gear(bool flag);

private:
    void update_battery(quint32 index);

    Ui::IconsBar *ui;

    Mcu::BatteryStatus m_batteryStatus[2];
    int m_batteryQuantity[2];
};

#endif // __ICONS_BAR_H__
