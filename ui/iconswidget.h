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

    QList<QPushButton*> pushButton_keyboard;

private:
    Ui::IconsWidget *ui;
    Mcu *m_mcu;

    void insert_battery1_icon(int value);
    void insert_battery2_icon(int value);

    Mcu::BatteryStatus m_batteryFirstStatus;
    Mcu::BatteryStatus m_batterySecondStatus;

protected slots:
    void on_pushButton_scan_clicked();
    void do_temperature_event(Mcu::TemperatureType type, int value);
    void do_battery_status_event(int index, Mcu::BatteryStatus status);
    void do_battery_quantity_event(int index, int value);

};

#endif // ICONSWIDGETS_H
