#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

#if (PHASCAN | PHASCAN_II)
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

    qDebug()<<"search_current_Dir = "<<qApp->applicationDirPath();

    int fontId = QFontDatabase::addApplicationFont(qApp->applicationDirPath() +"/SONGTI.TTC");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(fontName, 16);
    w.setFont(font);

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
#endif
    w.show();

    return a.exec();
}
