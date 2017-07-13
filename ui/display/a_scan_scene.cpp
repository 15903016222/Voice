/**
 * @file a_scan_scene.cpp
 * @brief A扫场景，显示A扫
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#include "a_scan_scene.h"

#include <QPainter>

#include <QDebug>

AscanScene::AscanScene(QObject *parent) :
    QGraphicsScene(parent),
    m_color("#ffff77")
{

}

QPainterPath AscanScene::wave_path(const QByteArray &wave, int w, int h)
{
    QPainterPath path;

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = h / 255.0;

    int drawPoints = 0;
    if ( wave.size() < w) {
        xRatio1 = w / 1.0 / wave.size();
        drawPoints = wave.size();
    } else {
        xRatio2 = wave.size() / 1.0 / w;
        drawPoints = w;
    }

    for (int i = 0; i < drawPoints; ++i) {
        path.lineTo( i*xRatio1,
                     ((quint8)(255-wave.at((int)(i*xRatio2)))) * yRatio - 0.5);
    }

    return path;
}

void AscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->translate(rect.topLeft());

    painter->setPen(m_color);
    painter->drawPath(wave_path(m_beam,
                                rect.size().toSize().width(),
                                rect.size().toSize().height()));
}
