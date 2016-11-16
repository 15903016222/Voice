#ifndef ICONSWIDGETS_H
#define ICONSWIDGETS_H

#include "myinputpanel.h"

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

    void insert_battery1_icon(int value);
    void insert_battery2_icon(int value);


signals:
    void keyboard_event();

public slots:
    void do_temperature_event(Mcu::TemperatureType type, int value);
    void do_battery_status_event(int index, Mcu::BatteryStatus status);
    void do_battery_quantity_event(int index, int value);

private:
    void update_battery(quint32 index);

    Ui::IconsBar *ui;
    Mcu *m_mcu;

    Mcu::BatteryStatus m_batteryStatus[2];
    int m_batteryQuantity[2];
};

#endif // ICONSWIDGETS_H
