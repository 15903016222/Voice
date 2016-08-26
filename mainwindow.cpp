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
            emit Imx_Sig_Query_Core_Temp();
            qDebug() << "Key_C, Query_Core_Temp";
            break;
        case Qt::Key_F://FPGA temperature
            emit Imx_Sig_Query_FPGA_Temp();
            qDebug() << "Key_F, Query_FPGA_Temp";
            break;

        case Qt::Key_D://POWERSUPPLY temperature
            emit Imx_Sig_Query_PowerSupply_Temp();
            qDebug() << "Key_D, Query_PowerSupply_Temp";
            break;
        case Qt::Key_M://MCU temperature
            emit Imx_Sig_Query_MCU_Temp();
            qDebug() << "Key_M, Query_MCU_Temp";
            break;

        case Qt::Key_A://battery 1
            emit Imx_Sig_Query_Battery();
            qDebug() << "Key_A, Query_Battery";
            break;
        case Qt::Key_B://battery 2
            emit Imx_Sig_Query_Battery2();
            qDebug() << "Key_B, Query_Battery2";
            break;
        case Qt::Key_G://Query_Brightness, back light
            emit Imx_Sig_Query_Brightness();
            qDebug() << "key G, Query_Brightness";
            break;
        case Qt::Key_L://back light
            emit Imx_Sig_Set_Brightness(qrand()%100);
            qDebug() << "key L, Set_Brightness";
            break;
        case Qt::Key_X://half1 data fot test;
            emit Imx_Sig_half1();
            qDebug() << "key X, Imx_Sig_half1";
            break;
        case Qt::Key_Y://half2 data for test;
            emit Imx_Sig_half2();
            qDebug() << "key Y, Imx_Sig_half2";
            break;
        case Qt::Key_Z://longdata for test;
            emit Imx_Sig_longdata();
            qDebug() << "key Z, long data!";
        break;
        case Qt::Key_0://longdata for test;
            emit Imx_Sig_main_APP_ready();
            qDebug() << "0:App ready";
            usleep(20000);
            emit Imx_Sig_Query_Core_Temp();
            qDebug() << "0:q core tem";
            usleep(20000);
            emit Imx_Sig_Query_FPGA_Temp();
            qDebug() << "0:q fpga temp";
            usleep(20000);
            emit Imx_Sig_Query_Battery();
            qDebug() << "0:q batt";
            usleep(20000);
            emit Imx_Sig_Query_Battery2();
            qDebug() << "0:q bat2";
            emit Imx_Sig_Query_BatteryStatus();
            qDebug() << "0:q bat2 status";
            usleep(20000);
            emit Imx_Sig_Query_Brightness();
            qDebug() << "0:query bright";
            usleep(20000);
            emit Imx_Sig_Set_Brightness(qrand()%100);
            qDebug() << "key 0, set Brightness";
        break;
        default:
            break;
        }
    /*发送信号*/
}
