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
    QGraphicsView(parent),
    m_orientation(Qt::Horizontal)
{
    setFocusPolicy(Qt::NoFocus);
    clearFocus();
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

ScanView::~ScanView()
{
}

void ScanView::set_orientation(Qt::Orientation orientation)
{
    if (m_orientation == orientation) {
        return;
    }

    if (orientation == Qt::Vertical) {
        rotate(90);
    } else {
        rotate(-90);
    }

    m_orientation = orientation;
}

void ScanView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    emit size_changed(event->size());
}
