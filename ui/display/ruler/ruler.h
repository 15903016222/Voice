#ifndef __RULER_H__
#define __RULER_H__

#include <QWidget>

#define CyanColor       "#249292"
#define DarkBlueColor   "#1D6765"
#define BlueColor       "#1F6E6C"
#define PaleGreenColor  "#A8D493"
#define GreenColor      "#239167"
#define YellowColor     "#D4DD46"
#define PalePinkColor   "#EAC8DF"
#define PinkColor       "#C174B0"
#define DarkPinkColor   "#EE2180"
#define PurpleColor     "#976594"
#define GreyColor       "#999B9E"
#define PaleGreyColor   "#C7CCCA"
#define DarkGreyColor   "#6B6B6E"

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

    Ruler(MarkPostion position=TOP, const QString &unit="", QWidget *parent = 0);
    explicit Ruler(QWidget *parent = 0);

    /**
     * @brief start 获取开始数据
     * @return      数据
     */
    double start() const;

    /**
     * @brief stop  获取结束数据
     * @return      数据
     */
    double stop() const;

    /**
     * @brief set_range 设置数据范围
     * @param start     开始数据
     * @param stop      结束数据
     */
    void set_range(double start, double stop);

    /**
     * @brief background_color  获取背景颜色
     * @return                  颜色
     */
    const QColor &background_color() const;

    /**
     * @brief set_background_color  设置背景颜色
     * @param color                 颜色
     */
    void set_background_color(const QColor &color);

    /**
     * @brief prec  获取显示数据的精度
     * @return      小数点几位
     */
    int prec();

    /**
     * @brief set_prec  设置显示数据的精度
     * @param prec      小数点几位
     */
    void set_prec(int prec);

    /**
     * @brief unit  获取单位字符串
     * @return      字符串
     */
    const QString &unit() const;

    /**
     * @brief set_unit_str  设置单位字符串
     * @param unit          字符串
     */
    void set_unit(const QString &unit);

    /**
     * @brief mark_position 获取刻度显示位置
     * @return              位置
     */
    MarkPostion mark_position() const;

    /**
     * @brief set_mark_position 设置刻度显示位置
     * @param position          位置
     */
    void set_mark_position(MarkPostion position);

    /**
     * @brief scroll    获取标尺是否为滚动状态
     * @return          true为滚动,false为不滚动
     */
    bool scroll() const;

    /**
     * @brief set_scroll    设置标尺滚动状态
     * @param flag          true为滚动,false为不滚动
     */
    void set_scroll(bool flag);

signals:
    void update_requested();

protected:
    void paintEvent(QPaintEvent *e);

    void draw_background(QPainter &painter);
    void draw_mark(QPainter &painter, int step, int markHeight, bool showVal=false);
    void draw_marks(QPainter &painter);

    /**
     * @brief first_mark_position   获取第一个刻度的位置
     * @return                      位置(像素)
     */
    double first_mark_position() const;

    /**
     * @brief first_mark_val    获取第一个刻度的数值
     * @return                  值(unit)
     */
    double first_mark_val() const;

    /**
     * @brief first_mark    获取步进step的刻度在步进1刻度中的第几个
     * @param step          表示隔step个步进为1的刻度
     * @return              第几个步进为1的刻度
     */
    int first_mark(int step) const;

    /**
     * @brief pixel_per_mark    获取一个刻度占用几个像素
     * @return                  像素
     */
    double pixel_per_mark() const;

    /**
     * @brief mark_qty  获取刻度数
     * @return          数量
     */
    int mark_qty() const;

    /**
     * @brief unit_per_mark 获取每刻度多少单位数据
     * @return              值(单位/刻度)
     */
    double unit_per_mark() const;

private:
    QColor m_bgColor;
    MarkPostion m_markPos;
    double m_start;
    double m_stop;
    int m_prec;
    QString m_unitStr;
    double m_pixelPerMark;
    bool m_scroll;
};

inline double Ruler::start() const
{
    return m_start;
}

inline double Ruler::stop() const
{
    return m_stop;
}

inline void Ruler::set_range(double start, double stop)
{
    m_start = start;
    m_stop = stop;
    emit update_requested();
}

inline const QColor &Ruler::background_color() const
{
    return m_bgColor;
}

inline void Ruler::set_background_color(const QColor &color)
{
    m_bgColor = color;
    update();
}

inline int Ruler::prec()
{
    return m_prec;
}

inline void Ruler::set_prec(int prec)
{
    m_prec = prec;
    update();
}

inline const QString &Ruler::unit() const
{
    return m_unitStr;
}

inline void Ruler::set_unit(const QString &unit)
{
    m_unitStr = unit;
    update();
}

inline Ruler::MarkPostion Ruler::mark_position() const
{
    return m_markPos;
}

inline void Ruler::set_mark_position(Ruler::MarkPostion position)
{
    m_markPos = position;
    update();
}

inline bool Ruler::scroll() const
{
    return m_scroll;
}

inline void Ruler::set_scroll(bool flag)
{
    m_scroll = flag;
    update();
}

inline double Ruler::unit_per_mark() const
{
    return (m_stop-m_start)/ mark_qty();
}

#endif // BASE_RULER_H
