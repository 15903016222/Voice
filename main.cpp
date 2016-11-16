#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QFontDatabase>

static const char *FONT_FILE = "/etc/mercury/font/SONGTI.TTC";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

#if (PHASCAN | PHASCAN_II)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    int fontId = QFontDatabase::addApplicationFont(FONT_FILE);
    QStringList list = QFontDatabase::applicationFontFamilies(fontId);
    if (list.isEmpty()) {
        qWarning()<<"font families is empty";
    } else {
        QFont font(list.at(0), 16);
        qDebug()<<"font="<<list.at(0);
        w.setFont(font);
    }

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    w.show();

    return a.exec();
}
