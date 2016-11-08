#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
#if (PHASCAN | PHASCAN_II)
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    w.show();

    return a.exec();
}
