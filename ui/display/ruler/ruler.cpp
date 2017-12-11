#include "ruler.h"
#include <QPainter>

static const int MIN_MARK_HIGHT = 2;
static const int MED_MARK_HIGHT = 5;
static const int MAX_MARK_HIGHT = 20;

Ruler::Ruler(QWidget *parent) : QWidget(parent),
    m_start(0),
    m_stop(100),
    m_pixelPerMark(10),
    m_prec(1),
    m_markPos(TOP),
    m_bgColor("#ff88ff")
{
}

Ruler::Ruler(MarkPostion position, const QString &unit, QWidget *parent) : QWidget(parent),
    m_start(0),
    m_stop(100),
    m_pixelPerMark(10),
    m_prec(1),
    m_markPos(position),
    m_unitStr(unit),
    m_bgColor("#ff88ff")
{
}

int Ruler::mark_qty() const
{
    if (m_markPos == TOP
            || m_markPos == BOTTOM) {
        return width() / m_pixelPerMark + 1;
    } else {
        return height() / m_pixelPerMark + 1;
    }
}

void Ruler::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setBrush(m_bgColor);
    painter.drawRect(rect());

    draw_marks(painter);
}

double Ruler::first_mark_position() const
{
    double flag = (m_start/unit_per_mark()) - (int)(m_start/unit_per_mark());
    if (flag > 0.000000000001) {
        return (1-flag) * m_pixelPerMark;
    } else if(flag < -0.000000000001) {
        return qAbs(flag*m_pixelPerMark);
    }
    return 0.0;
}

double Ruler::first_mark_val() const
{
    double flag = (m_start/unit_per_mark()) - (int)(m_start/unit_per_mark());

    if (flag > 0.000000000001) {
        return m_start + (1-flag) * unit_per_mark();
    } else if(flag < -0.000000000001) {
        return m_start - flag*unit_per_mark();
    }
    return m_start;
}

int Ruler::first_mark(int step) const
{
    int ret = (int)(qAbs(first_mark_val()/unit_per_mark())+0.5)%step;
    if ( (m_start < m_stop && first_mark_val() > 0 && ret > 0)
         || ( m_start > m_stop && first_mark_val() < 0 && ret > 0) ) {
        ret = step - ret;
    }
    return ret;
}

void Ruler::draw_mark(QPainter &painter, int step, int markHeight, bool showVal)
{
    double fstMarkPos = first_mark_position();

    /* draw mark */
    for (int i = first_mark(step); i < mark_qty(); i += step) {
        painter.drawLine(fstMarkPos+i*m_pixelPerMark, 0,
                         fstMarkPos+i*m_pixelPerMark, markHeight);
    }

    if (showVal) {
        /* draw text */
        painter.drawText(fstMarkPos + first_mark(step)*m_pixelPerMark + 1, markHeight,
                         QString::number(first_mark_val() + first_mark(step)*unit_per_mark(), 'f', m_prec)+m_unitStr);

        for (int i = first_mark(step)+step; i < mark_qty(); i += step) {
            painter.drawText(fstMarkPos + i*m_pixelPerMark + 1, markHeight,
                             QString::number(first_mark_val() + i*unit_per_mark(), 'f', m_prec));
        }
    }
}

void Ruler::draw_marks(QPainter &painter)
{
    painter.save();
    painter.setPen(Qt::black);

    if (m_markPos == RIGHT) {
        painter.rotate(90);
        painter.translate(0, -width());
    } else if (m_markPos == LEFT) {
        painter.rotate(-90);
        painter.translate(-height(), 0);
    } else if (m_markPos == BOTTOM) {
        painter.rotate(180);
        painter.translate(-width(), -height());
    }

    draw_mark(painter, 1, MIN_MARK_HIGHT);
    draw_mark(painter, 5, MED_MARK_HIGHT);
    draw_mark(painter, 10, MAX_MARK_HIGHT, true);

    painter.restore();
}
