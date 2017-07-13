#ifndef __A_SCAN_SCENE_H__
#define __A_SCAN_SCENE_H__

#include <QGraphicsScene>

class AscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AscanScene(Qt::Orientation orientation = Qt::Horizontal, QObject *parent = 0);

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
     * @brief wave_orientation  获取显示方向
     * @return                  方向
     */
    Qt::Orientation wave_orientation() const;

    /**
     * @brief set_wave_orientation  设置显示方向
     * @param orientation           方向
     */
    void set_wave_orientation(Qt::Orientation orientation);

    /**
     * @brief show  显示波形
     * @param b     波形数据
     */
    void set_wave(const QByteArray &b);

protected:
    QPainterPath wave_path(const QByteArray &wave, int w, int h);

    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QColor m_color;
    QByteArray m_beam;
    Qt::Orientation m_orientation;
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

inline Qt::Orientation AscanScene::wave_orientation() const
{
    return m_orientation;
}

inline void AscanScene::set_wave_orientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
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
