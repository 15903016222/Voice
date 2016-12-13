#ifndef __RULER_WIDGET_H__
#define __RULER_WIDGET_H__

#include <QWidget>

class RulerWidget : public QWidget
{
    Q_OBJECT
public:
    enum DirectionType {

    };

    explicit RulerWidget(QWidget *parent = 0);

    bool set_range(double start, double end);
    void set_unit(const QString &unit);
    void set_backgroup_color(QColor &color);
//    void set_step()

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);

private:
    double m_start;
    double m_end;

    QColor m_color;

    DirectionType m_direction;
};

#endif // __RULER_WIDGET_H__
