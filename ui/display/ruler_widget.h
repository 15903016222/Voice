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

    bool set_range(double start, double end);
    void set_unit(const QString &unit) { m_unitName = unit; }
    void set_backgroup_color(const QColor &color) { m_bgColor = color; }
    void set_type(RulerWidget::Type type) { m_type = type; }
    void set_direction(RulerWidget::Direction direction) { m_direction = direction; }
    void move_pix(unsigned int step);

protected:
    int y_axis_length() const;

    void paintEvent(QPaintEvent *e);

private:
    double m_start;
    double m_end;
    QString m_unitName;

    QColor m_bgColor;

    Type m_type;
    Direction m_direction;
    int     m_move;
    int     m_step;
    int     m_moveUnit;
    int     m_offset;
    double  m_totalMove;
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
