#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
        {
        case Qt::Key_P://power,
            qDebug() << "key P";
            break;
        case Qt::Key_B://battery 1
            qDebug() << "key B";
            break;
        case Qt::Key_C://battery 2
            qDebug() << "key C";
            break;
        case Qt::Key_D://battery 3
            qDebug() << "key D";
            break;
        case Qt::Key_L://back light
            qDebug() << "key L";
            break;
        case Qt::Key_T://temperue
            qDebug() << "key T";
            break;
        case Qt::Key_A://probe
            qDebug() << "key A";
            break;
        case Qt::Key_K://key
            qDebug() << "key K";
            break;
        case Qt::Key_R://rotary
            qDebug() << "key R";
            break;
        case Qt::Key_0:
            qDebug() << "key 0";
            break;
        case Qt::Key_1:
            qDebug() << "key 1";
            break;
        case Qt::Key_2:
            qDebug() << "key 2";
            break;
        case Qt::Key_3:
            qDebug() << "key 3";
            break;
        case Qt::Key_4:
            qDebug() << "key 4";
            break;
        case Qt::Key_5:
            qDebug() << "key 5";
            break;
        case Qt::Key_6:
            qDebug() << "key 6";
            break;
        case Qt::Key_7:
            qDebug() << "key 7";
            break;
        case Qt::Key_8:
            qDebug() << "key 8";
            break;
        case Qt::Key_9:
            qDebug() << "key 9";
            break;
        }
}
