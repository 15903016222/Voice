#include "mode_list_widget_item.h"
#include <QDebug>

const int ModeListWidgetItem::H_SIZE = 60;
const int ModeListWidgetItem::W_SIZE = 60;

ModeListWidgetItem::ModeListWidgetItem(DplDisplay::Display::Mode mode) :
    m_mode(mode)
{
    QPixmap pixmap(":/file/resources/logo.png");
    setIcon(QIcon(pixmap.scaled(QSize(W_SIZE, H_SIZE))));
    setSizeHint(QSize(W_SIZE, H_SIZE));
}
