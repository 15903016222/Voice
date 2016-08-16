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

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));


    Mcu *stm32_serial_p = Mcu::get_mcu();
    qDebug("get_mcu: %lu\n", (long unsigned int)stm32_serial_p);


    return a.exec();
}

