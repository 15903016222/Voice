#include "mainwindow.h"
#include <QApplication>
#include <mcu/mcu.h>
#include <QDebug>
#include <QTime>
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

    QObject::connect(&w, &MainWindow::Imx_Sig_Query_Core_Temp, stm32_serial_p, &Mcu::query_core_temp);
    QObject::connect(&w, &MainWindow::Imx_Sig_Query_FPGA_Temp, stm32_serial_p, &Mcu::query_FPGA_temp);
    QObject::connect(&w, &MainWindow::Imx_Sig_Query_PowerSupply_Temp, stm32_serial_p, &Mcu::query_PowerSupply_temp);
    QObject::connect(&w, &MainWindow::Imx_Sig_Query_MCU_Temp, stm32_serial_p, &Mcu::query_MCU_temp);
    QObject::connect(&w, &MainWindow::Imx_Sig_Query_Battery, stm32_serial_p, &Mcu::query_battery);
    QObject::connect(&w, &MainWindow::Imx_Sig_Query_Battery2, stm32_serial_p, &Mcu::query_battery2);
    QObject::connect(&w, &MainWindow::Imx_Sig_Query_Brightness, stm32_serial_p, &Mcu::query_brightness);
    QObject::connect(&w, &MainWindow::Imx_Sig_Set_Brightness, stm32_serial_p, &Mcu::set_brightness);
    /*just for test*/
    QObject::connect(&w, &MainWindow::Imx_Sig_half1, stm32_serial_p, &Mcu::query_half1);
    QObject::connect(&w, &MainWindow::Imx_Sig_half2, stm32_serial_p, &Mcu::query_half2);
    QObject::connect(&w, &MainWindow::Imx_Sig_longdata, stm32_serial_p, &Mcu::query_longdata);
    /*just for test end*/
    return a.exec();
}

