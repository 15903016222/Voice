/**
 * @file a_scan_image.cpp
 * @brief 画A扫图片
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-12
 */
#include "a_scan_image.h"

#include <QPainter>

AscanImage::AscanImage(const QSize &size, const QByteArray &wave, const QColor &waveColor, const QColor &backGroundColor) :
    QImage(size, QImage::Format_RGB16)
{
    fill(backGroundColor);
    set_wave(wave, waveColor);
}

QPainterPath AscanImage::wave_path(const QByteArray &wave)
{
    QPainterPath path;

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = height() / 255.0;

    int drawPoints = 0;
    if ( wave.size() < width()) {
        xRatio1 = width() / 1.0 / wave.size();
        drawPoints = wave.size();
    } else {
        xRatio2 = wave.size() / 1.0 / width();
        drawPoints = width();
    }

    for (int i = 0; i < drawPoints; ++i) {
        path.lineTo( i*xRatio1,
                     ((quint8)(wave.at((int)(i*xRatio2)))) * yRatio + 0.5);
    }

    return path;
}

void AscanImage::set_wave(const QByteArray &wave, const QColor &color)
{
    QPainter painter(this);
    painter.translate(0, height());

    QTransform form = painter.transform();
    form.rotate(180, Qt::XAxis);
    painter.setTransform(form);

    painter.setPen(color);
    painter.drawPath(wave_path(wave));
}
