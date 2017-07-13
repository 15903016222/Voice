/**
 * @file a_scan_view.h
 * @brief A扫视图
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_VIEW_H__
#define __A_SCAN_VIEW_H__

#include <QGraphicsView>

class AscanView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AscanView(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = 0);
    ~AscanView();

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
     * @brief orientation   获取显示方向
     * @return              方向
     */
    Qt::Orientation orientation() const;

    /**
     * @brief set_orientation   设置显示方向
     * @param orientation       方向
     */
    void set_orientation(Qt::Orientation orientation);

    /**
     * @brief show  显示波形
     * @param b     波形数据
     */
    void set_wave(const QByteArray &b);

protected:
    /**
     * @brief x_axis_length     获取X轴长度
     * @return                  长度(Pixel)
     */
    virtual int x_axis_length() const = 0;

    /**
     * @brief y_axis_length     获取Y轴长度
     * @return                  长度(Pixel)
     */
    virtual int y_axis_length() const = 0;

    virtual void resizeEvent(QResizeEvent *event);

    QPainterPath wave_path(const QByteArray &wave, int w, int h);

    void drawBackground(QPainter *painter, const QRectF &rect);
signals:

private:
    QColor m_color;
    QByteArray m_beam;
    QGraphicsScene m_scene;
    Qt::Orientation m_orientation;
};

inline const QColor &AscanView::wave_color() const
{
    return m_color;
}

inline void AscanView::set_wave_color(const QColor &color)
{
    m_color = color;
}

inline Qt::Orientation AscanView::orientation() const
{
    return m_orientation;
}

inline void AscanView::set_orientation(Qt::Orientation orientation)
{
    m_orientation = orientation;
}


#endif // __A_SCAN_VIEW_H__
