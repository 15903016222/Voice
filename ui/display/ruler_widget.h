#ifndef __RULER_WIDGET_H__
#define __RULER_WIDGET_H__

#include <QWidget>

class RulerWidget : public QWidget
{
    Q_OBJECT
public:
    enum Type {
        LEFT,
        RIGHT,
        BOTTOM
    };
    enum Direction {
        Up,
        Down
    };

    explicit RulerWidget(QWidget *parent = 0);

<<<<<<< HEAD
    virtual bool set_range(double start, double end);
=======
    /**
     * @brief set_range 设置标尺范围
     * @param start     开始数
     * @param end       结束数
     * @return          成功返回true,失败返回false
     */
    bool set_range(double start, double end);

    /**
     * @brief set_unit  设置标尺显示单位
     * @param unit      单位,字符
     */
>>>>>>> 5ea24c39331e6d74f8f9e54238878abb6161cd09
    void set_unit(const QString &unit) { m_unitName = unit; }

    /**
     * @brief set_backgroup_color   设置背景颜色
     * @param color                 颜色
     */
    void set_backgroup_color(const QColor &color) { m_bgColor = color; }

    /**
     * @brief set_type  设置标尺的位置类型
     * @param type      类型
     */
    void set_type(RulerWidget::Type type) { m_type = type; }

    /**
     * @brief set_direction 设置数字增减方向
     * @param direction     方向
     */
    void set_direction(RulerWidget::Direction direction) { m_direction = direction; }

protected:
    int y_axis_length() const;

    virtual void paintEvent(QPaintEvent *e);

<<<<<<< HEAD
=======
protected:
>>>>>>> 5ea24c39331e6d74f8f9e54238878abb6161cd09
    double m_start;
    double m_end;
    QString m_unitName;

    QColor m_bgColor;

    Type m_type;
    Direction m_direction;
};

inline int RulerWidget::y_axis_length() const
{
    if (RulerWidget::BOTTOM == m_type) {
        return width();
    } else {
        return height();
    }
}
#endif // __RULER_WIDGET_H__
