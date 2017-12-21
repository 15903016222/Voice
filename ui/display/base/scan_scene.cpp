/**
 * @file scan_scene.cpp
 * @brief Scan场景
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#include "scan_scene.h"
#include "QPainter"

ScanScene::ScanScene(QObject *parent) :
    QGraphicsScene(parent)
{
    connect(this, SIGNAL(update_requested()),
            this, SLOT(update()), Qt::QueuedConnection);
}

void ScanScene::update()
{
    QGraphicsScene::update();
}

void ScanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QReadLocker l(&m_rwlock);
    if (m_pixmap.isNull()) {
        return;
    }
    painter->drawPixmap(rect, m_pixmap, m_pixmap.rect());
}
