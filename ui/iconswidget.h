#ifndef ICONSWIDGETS_H
#define ICONSWIDGETS_H

#include "myinputpanel.h"

#include "mcu.h"

#include <QWidget>

namespace Ui {
class IconsWidget;
}

class IconsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IconsWidget(QWidget *parent = 0);
    ~IconsWidget();

private:
    Ui::IconsWidget *ui;
    Mcu *m_mcu;

public:
    Mcu::BatteryStatus status_batteryFirst;
    Mcu::BatteryStatus status_batterySecond;

    void insert_battery1_icon(int value);
    void insert_battery2_icon(int value);

signals:

public slots:
    void on_pushButton_keyboard_clicked();
    void on_pushButton_scan_clicked();
    void do_rotary_event(Mcu::RotaryType type);
    void do_temperature_event(Mcu::TemperatureType type, int value);
    void do_battery_status_event(int index, Mcu::BatteryStatus status);
    void do_battery_quantity_event(int index, int value);

};

#endif // ICONSWIDGETS_H
