#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../mcu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void do_verticalSliderBrightness_value_changed(int value);
    void do_rotary_event(Mcu::RotaryType type);
    void do_battery_status_event(int index, Mcu::BatteryStatus status);
    void do_battery_quantity_event(int index, int value);
    void do_temperature_event(Mcu::TemperatureType type, int value);
    void do_probe_event(const Probe& probe);

private slots:
    void on_pushButtonStarted_clicked();

private:
    Ui::MainWindow *ui;
    Mcu *m_mcu;
};

#endif // MAINWINDOW_H
