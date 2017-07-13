/**
 * @file a_scan_view.cpp
 * @brief A扫视图
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#include "a_scan_view.h"

#include <QResizeEvent>
#include <QDebug>

AscanView::AscanView(QWidget *parent):
    QGraphicsView(parent)
{
    setStyleSheet("QGraphicsView {"
                  "border: 0px;"
                  "}");
//    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint
//                        | Qt::WindowTitleHint | Qt::FramelessWindowHint);
}

AscanView::~AscanView()
{
}

void AscanView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(0, 0, event->size().width(), event->size().height());
    }
    QGraphicsView::resizeEvent(event);
}
