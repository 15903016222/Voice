/**
 * @file a_scan_scene.h
 * @brief A扫场景，显示A扫
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 
 * @date 2017-07-13
 */
#ifndef __A_SCAN_SCENE_H__
#define __A_SCAN_SCENE_H__

#include <QGraphicsScene>

class AscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AscanScene(QObject *parent = 0);

    /**
     * @brief wave_color    获取波型显示颜色
     * @return              颜色
     */
    const QColor &wave_color() const;

    /**
     * @brief set_wave_color    设置波形显示颜色
     * @param color             颜色
     */
    void set_wave_color(const QColor &color);

    /**
     * @brief show  显示波形
     * @param b     波形数据
     */
    void set_wave(const QByteArray &b);

protected:
    /**
     * @brief wave_path 画波形路径
     * @param wave      波形数据
     * @param w         画板宽度
     * @param h         画板高度
     * @return          返回波形路径，以左上角为原点，向右为X轴正方向，向下为Y轴正方向
     */
    QPainterPath wave_path(const QByteArray &wave, int w, int h);

    /**
     * @brief drawBackground    画场景背景
     * @param painter           QPainter
     * @param rect              区域
     */
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QColor m_color;
    QByteArray m_beam;
};

inline const QColor &AscanScene::wave_color() const
{
    return m_color;
}

inline void AscanScene::set_wave_color(const QColor &color)
{
    m_color = color;
    update();
}

inline void AscanScene::set_wave(const QByteArray &b)
{
    if (! b.isEmpty()) {
        m_beam.setRawData(b.constData(), b.size());
        update();
    }
}

#endif // __A_SCAN_SCENE_H__
