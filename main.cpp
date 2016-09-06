#include "mainwindow.h"
#include <QApplication>
#include <mcu/mcu.h>
#include <QDebug>
#include <QTime>
#include "stdint.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    Mcu *stm32_serial_p = Mcu::get_mcu();
    qDebug("get_mcu: %lu\n", (long unsigned int)stm32_serial_p);

    QObject::connect(&w, &MainWindow::imx_sig_query_core_temp, stm32_serial_p, &Mcu::query_core_temp);
    QObject::connect(&w, &MainWindow::imx_sig_query_FPGA_temp, stm32_serial_p, &Mcu::query_fpga_temp);
    QObject::connect(&w, &MainWindow::imx_sig_query_power_supply_temp, stm32_serial_p, &Mcu::query_power_temp);
    QObject::connect(&w, &MainWindow::imx_sig_query_MCU_temp, stm32_serial_p, &Mcu::query_mcu_temp);

    QObject::connect(&w, &MainWindow::imx_sig_query_battery, stm32_serial_p, &Mcu::query_battery);
    QObject::connect(&w, &MainWindow::imx_sig_query_battery2, stm32_serial_p, &Mcu::query_battery2);
    QObject::connect(&w, &MainWindow::imx_sig_query_battery_status, stm32_serial_p, &Mcu::query_battery_status);
    QObject::connect(&w, &MainWindow::imx_sig_query_battery2_status, stm32_serial_p, &Mcu::query_battery2_status);

    QObject::connect(&w, &MainWindow::imx_sig_query_brightness, stm32_serial_p, &Mcu::query_brightness);
    QObject::connect(&w, &MainWindow::imx_sig_set_brightness, stm32_serial_p, &Mcu::set_brightness);
    QObject::connect(&w, &MainWindow::imx_sig_main_APP_ready, stm32_serial_p, &Mcu::notify_started);

    return a.exec();
}

