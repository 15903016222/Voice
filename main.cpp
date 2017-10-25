#include "mainwindow.h"
#include <device/device.h>
#include <QApplication>
#include <QTextCodec>
#include <QFontDatabase>
#include <QSplashScreen>
#include <QTime>

#if (PHASCAN | PHASCAN_II)
static const char *FONT_FILE = "/opt/mercury/font/Arial.ttf";
#endif
#if (PC_UNIX | PC_WIN)
static const char *FONT_FILE = "Arial.ttf";
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(QLatin1String("Mercury"));
//    a.setApplicationVersion();

    QSplashScreen splash(QPixmap("/opt/mercury/image/splash.png"));
    splash.show();
    a.processEvents();

    QTime time;
    time.restart();
    DplDevice::Device::instance()->add_group();
    qDebug("Mercury Starting");

    MainWindow w;

    int fontId = QFontDatabase::addApplicationFont(FONT_FILE);
    QStringList list = QFontDatabase::applicationFontFamilies(fontId);
    if (list.isEmpty()) {
        qWarning("font families is empty");
    } else {
        QFont font(list.at(0), 16);
        w.setFont(font);
    }

#if PHASCAN
//    QApplication::setOverrideCursor(Qt::BlankCursor);       // 隐藏鼠标
    w.setCursor(Qt::BlankCursor);                           // 隐藏鼠标
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#elif PHASCAN_II
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif

    w.show();

    DplDevice::Device::instance()->start();

    qDebug("%s[%d]: Take Time: %d(ms)",__func__, __LINE__, time.elapsed());

    splash.finish(&w);
    return a.exec();
}
