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
    void Imx_Sig_Query_Core_Temp();
    void Imx_Sig_Query_FPGA_Temp();
    void Imx_Sig_Query_PowerSupply_Temp();
    void Imx_Sig_Query_MCU_Temp();

    void Imx_Sig_Query_Battery();
    void Imx_Sig_Query_Battery2();

    void Imx_Sig_Query_BatteryStatus();
    void Imx_Sig_Query_Battery2Status();

    void Imx_Sig_Query_Brightness();
    void Imx_Sig_Set_Brightness(uint8_t light);

    void Imx_Sig_Poweroff();
    void Imx_Sig_Key();
    void Imx_Sig_Rotary();
    void Imx_Sig_main_APP_ready();
    void Imx_Sig_STM32_power_off();


    /* just for test */
    void Imx_Sig_half1();
    void Imx_Sig_half2();
    void Imx_Sig_longdata();
    /* just for test end*/
private:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
