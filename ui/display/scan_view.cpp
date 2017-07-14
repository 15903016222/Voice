/**
 * @file scan_view.cpp
 * @brief scan视图
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#include "scan_view.h"
#include <QResizeEvent>
#include <QDebug>
ScanView::ScanView(QWidget *parent):
    QGraphicsView(parent)
{
    setStyleSheet("QGraphicsView {"
                  "border: 0px;"
                  "}");
//    setWindowFlags(Qt::Window | Qt::CustomizeWindowHint
//                        | Qt::WindowTitleHint | Qt::FramelessWindowHint);
}

ScanView::~ScanView()
{
}

void ScanView::resizeEvent(QResizeEvent *event)
{
    emit size_changed(event->size());

    QGraphicsView::resizeEvent(event);
}
