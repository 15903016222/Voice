/**
 * @file a_scan_widget.h
 * @brief 画A扫
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_WIDGET_H__
#define __A_SCAN_WIDGET_H__

#include <QWidget>

class AscanWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AscanWidget(QWidget *parent = 0);

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
    void show(const QByteArray &b);

    enum GateType {
        GATE_A,
        GATE_B,
        GATE_I
    };

public slots:
    /**
     * @brief set_sample    设置采样信息
     * @param start         采样起点(ns)
     * @param range         采样范围(ns)
     */
    void set_sample(float start, float range);

    /**
     * @brief set_gate  设置闸门信息
     * @param type      闸门类型
     * @param start     闸门起点(ns)
     * @param width     闸门宽度(ns)
     */
    void set_gate(AscanWidget::GateType type, float start, float width);

    /**
     * @brief set_gate_visible  设置闸门是否显示
     * @param type              闸门类型
     * @param visible           显示标志
     */
    void set_gate_visible(bool visible);

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


    /**
     * @brief paint_wave    画波形
     * @return              路径
     */
    QPainterPath paint_wave();

    /**
     * @brief paint_gate    画闸门
     * @return              路径
     */
    QPainterPath paint_gate();

signals:

private:
    QByteArray m_beam;
    QColor m_color;
    float m_sampleStart;
    float m_sampleRange;
    float m_gateStart[3];
    float m_gateWidth[3];
    bool m_gateVisible[3];
};

inline const QColor &AscanWidget::wave_color() const
{
    return m_color;
}

inline void AscanWidget::set_wave_color(const QColor &color)
{
    m_color = color;
}

inline void AscanWidget::set_sample(float start, float range)
{
    m_sampleStart = start;
    m_sampleRange = range;
}

inline void AscanWidget::set_gate(AscanWidget::GateType type, float start, float width)
{
    Q_ASSERT( type >= GATE_A && type <= GATE_I );
    m_gateStart[type] = start;
    m_gateWidth[type] = width;
}

inline void AscanWidget::set_gate_visible(bool visible)
{
//    Q_ASSERT( type >= GATE_A && type <= GATE_I );
//    m_gateVisible[type] = visible;
}


#endif // __A_SCAN_WIDGET_H__
