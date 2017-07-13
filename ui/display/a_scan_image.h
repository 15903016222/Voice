/**
 * @file a_scan_image.h
 * @brief 画A扫图片
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-12
 */
#ifndef __A_SCAN_IMAGE_H__
#define __A_SCAN_IMAGE_H__

#include <QColor>
#include <QImage>

class AscanImage : public QImage
{
public:
    explicit AscanImage(const QSize &size, const QByteArray &wave, const QColor &waveColor, const QColor &backGroundColor = Qt::black);

protected:
    /**
     * @brief show  显示波形
     * @param wave  波形数据
     * @param color 波形显示颜色
     */
    void set_wave(const QByteArray &wave, const QColor &color);

    /**
     * @brief draw_wave 画波形路径
     * @param wave      波形数据
     * @return          路径
     */
    QPainterPath wave_path(const QByteArray &wave);
};

#endif // __A_SCAN_IMAGE_H__
