#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QKeyEvent>
#include "stdint.h"
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

Q_SIGNALS:
    void imx_sig_query_core_temp();
    void imx_sig_query_FPGA_temp();
    void imx_sig_query_power_supply_temp();
    void imx_sig_query_MCU_temp();

    void imx_sig_query_battery();
    void imx_sig_query_battery2();

    void imx_sig_query_battery_status();
    void imx_sig_query_battery2_status();

    void imx_sig_query_brightness();
    void imx_sig_set_brightness(uint8_t light);

    void imx_sig_poweroff();
    void imx_sig_key();
    void imx_sig_rotary();
    void imx_sig_main_APP_ready();
    void imx_sig_STM32_power_off();


    /* just for test */
    void imx_sig_half1();
    void imx_sig_half2();
    void imx_sig_longdata();
    /* just for test end*/
private:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
