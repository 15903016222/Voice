#ifndef __RULER_H__
#define __RULER_H__

#include <QWidget>

class Ruler : public QWidget
{
    Q_OBJECT
public:
    enum MarkPostion {
        TOP,
        BOTTOM,
        RIGHT,
        LEFT
    };

    explicit Ruler(QWidget *parent=0);
    explicit Ruler(MarkPostion position=TOP, const QString &unit="", QWidget *parent = 0);

    /**
     * @brief set_range 设置数据范围
     * @param start     开始数据
     * @param stop      结束数据
     */
    void set_range(double start, double stop);

    /**
     * @brief mark_qty  获取刻度数量
     * @return          数量
     */
    int mark_qty() const;

    /**
     * @brief unit_per_mark 获取每刻度多少单位数据
     * @return              值(单位/刻度)
     */
    double unit_per_mark() const;

    /**
     * @brief set_prec  Setting the precision of the showing value
     * @param prec      precision
     */
    void set_prec(int prec);

    /**
     * @brief set_unit_str  设置单位字符串
     * @param unit          字符串
     */
    void set_unit(const QString &unit);

    /**
     * @brief set_background_color  设置背景颜色
     * @param color                 颜色
     */
    void set_background_color(const QColor &color);

protected:
    void paintEvent(QPaintEvent *e);

    /**
     * @brief first_mark_position   Get the position of the first Mark
     * @return                      position(pixel)
     */
    double first_mark_position() const;

    /**
     * @brief first_mark_val    Get value of the first mark
     * @return                  value(unit)
     */
    double first_mark_val() const;

    /**
     * @brief first_mark
     * @return
     */
    int first_mark(int step) const;

    void draw_mark(QPainter &painter, int step, int markHeight, bool showVal=false);
    void draw_marks(QPainter &painter);

private:
    double m_start;
    double m_stop;
    int m_pixelPerMark;         // pixel/mark
    int m_prec;                 // show precision of the value text
    MarkPostion m_markPos;      // the position of the mark showing
    QString m_unitStr;
    QColor m_bgColor;
};

inline void Ruler::set_range(double start, double stop)
{
    m_start = start;
    m_stop = stop;
    update();
}

inline double Ruler::unit_per_mark() const
{
    return (m_stop-m_start)/ (mark_qty()-1);
}

inline void Ruler::set_prec(int prec)
{
    m_prec = prec;
    update();
}

inline void Ruler::set_unit(const QString &unit)
{
    m_unitStr = unit;
    update();
}

inline void Ruler::set_background_color(const QColor &color)
{
    m_bgColor = color;
    update();
}

#endif // __RULER_H__
