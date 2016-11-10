#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    int fontId = QFontDatabase::addApplicationFont(":/file/resources/SIMSUN.TTC");
    QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(msyh, 16);

    MainWindow w;
    w.setFont(font);
#if (PHASCAN | PHASCAN_II)
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    w.show();

    return a.exec();
}
