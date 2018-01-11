#include "mainwindow.h"
#include <global.h>
#include <device/device.h>
#include <QApplication>
#include <QSplashScreen>
#include <QTextCodec>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QLatin1String("Mercury"));
//    a.setApplicationVersion();

    QTime time;
    time.restart();

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
#endif

    QSplashScreen splash(QPixmap(IMAGE_PATH"/splash.png"));
    splash.show();
    a.processEvents();

    DplDevice::Device::instance()->add_group();
    qDebug("Mercury Starting");

    MainWindow w;

#if PHASCAN || PHASCAN_II
//    w.setCursor(Qt::BlankCursor);                           // 隐藏鼠标
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif

    w.show();

    DplDevice::Device::instance()->start();

    splash.finish(&w);

    qDebug("%s[%d]: Take Time: %d(ms)",__func__, __LINE__, time.elapsed());

    return a.exec();
}
