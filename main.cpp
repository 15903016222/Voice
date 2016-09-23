#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    int r = 0;
    QApplication a(argc, argv);

    MainWindow w;
 //   w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    r = a.exec();

    return r;
}
