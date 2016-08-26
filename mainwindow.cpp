#include "mainwindow.h"
#include <QDebug>
#include <QTime>
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    switch (event->key())
        {
        case Qt::Key_C://core board temperature
            emit imx_sig_query_core_temp();
            qDebug() << "Key_C, Query_Core_temp";
            break;
        case Qt::Key_F://FPGA temperature
            emit imx_sig_query_FPGA_temp();
            qDebug() << "Key_F, Query_FPGA_temp";
            break;

        case Qt::Key_D://POWERSUPPLY temperature
            emit imx_sig_query_power_supply_temp();
            qDebug() << "Key_D, query_power_supply_temp";
            break;
        case Qt::Key_M://MCU temperature
            emit imx_sig_query_MCU_temp();
            qDebug() << "Key_M, Query_MCU_temp";
            break;

        case Qt::Key_A://battery 1
            emit imx_sig_query_battery();
            qDebug() << "Key_A, Query_Battery";
            break;
        case Qt::Key_B://battery 2
            emit imx_sig_query_battery2();
            qDebug() << "Key_B, Query_Battery2";
            break;
        case Qt::Key_G://Query_Brightness, back light
            emit imx_sig_query_brightness();
            qDebug() << "key G, Query_Brightness";
            break;
        case Qt::Key_L://back light
            emit imx_sig_set_brightness(qrand()%100);
            qDebug() << "key L, Set_Brightness";
            break;
        case Qt::Key_X://half1 data fot test;
            emit imx_sig_half1();
            qDebug() << "key X, imx_sig_half1";
            break;
        case Qt::Key_Y://half2 data for test;
            emit imx_sig_half2();
            qDebug() << "key Y, imx_sig_half2";
            break;
        case Qt::Key_Z://longdata for test;
            emit imx_sig_longdata();
            qDebug() << "key Z, long data!";
        break;
        case Qt::Key_0://longdata for test;
            emit imx_sig_main_APP_ready();
            qDebug() << "0:App ready";
            usleep(20000);
            emit imx_sig_query_core_temp();
            qDebug() << "0:q core tem";
            usleep(20000);
            emit imx_sig_query_FPGA_temp();
            qDebug() << "0:q fpga temp";
            usleep(20000);
            emit imx_sig_query_battery();
            qDebug() << "0:q batt";
            usleep(20000);
            emit imx_sig_query_battery2();
            qDebug() << "0:q bat2";
            emit imx_sig_query_battery_status();
            qDebug() << "0:q bat2 status";
            usleep(20000);
            emit imx_sig_query_brightness();
            qDebug() << "0:query bright";
            usleep(20000);
            emit imx_sig_set_brightness(qrand()%100);
            qDebug() << "key 0, set Brightness";
        break;
        default:
            break;
        }
    /*发送信号*/
}
