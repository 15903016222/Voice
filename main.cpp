#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
#ifndef _WINDOWS_
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    w.show();

    return a.exec();
}
