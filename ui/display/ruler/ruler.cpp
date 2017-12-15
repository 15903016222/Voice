#include "ruler.h"
#include <QPainter>

static const int MIN_MARK_HIGHT = 2;
static const int MED_MARK_HIGHT = 5;
static const int MAX_MARK_HIGHT = 18;

Ruler::Ruler(Ruler::MarkPostion position, const QString &unit, QWidget *parent) : QWidget(parent),
    m_bgColor(YellowColor),
    m_markPos(position),
    m_start(0),
    m_stop(100),
    m_prec(1),
    m_unitStr(unit),
    m_pixelPerMark(10),
    m_scroll(false)
{
    if (position == RIGHT
            ||position == LEFT) {
        setMinimumWidth(20);
    } else {
        setMinimumHeight(20);
    }

    connect(this, SIGNAL(update_requested()),
            this, SLOT(update()), Qt::QueuedConnection);
}

Ruler::Ruler(QWidget *parent) : QWidget(parent),
    m_bgColor("#ff88ff"),
    m_markPos(Ruler::TOP),
    m_start(0),
    m_stop(100),
    m_prec(1),
    m_unitStr(""),
    m_pixelPerMark(10),
    m_scroll(false)
{

}

void Ruler::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter painter(this);

    draw_background(painter);

    draw_marks(painter);
}

void Ruler::draw_background(QPainter &painter)
{
    painter.save();
    painter.setBrush(m_bgColor);
    painter.drawRect(rect());
    painter.restore();
}


void Ruler::draw_marks(QPainter &painter)
{
    painter.save();
    painter.setPen(Qt::black);

    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);

    if (m_markPos == RIGHT) {
        painter.rotate(90);
        painter.translate(0, -width());
    } else if (m_markPos == LEFT) {
        painter.rotate(-90);
        painter.translate(-height(), 0);
    } else if (m_markPos == BOTTOM) {
        painter.rotate(180);
        painter.translate(-width(),
                          -height());
    }

    draw_mark(painter, 1, MIN_MARK_HIGHT);
    draw_mark(painter, 5, MED_MARK_HIGHT);
    draw_mark(painter, 10, MAX_MARK_HIGHT, true);

    painter.restore();
}

double Ruler::first_mark_position() const
{
    if (m_scroll) {
        double flag = (start()/unit_per_mark()) - (int)(start()/unit_per_mark());
        if (flag > 0.000000000001) {
            return (1-flag) * pixel_per_mark();
        } else if(flag < -0.000000000001) {
            return qAbs(flag*pixel_per_mark());
        }
    }
    return 0.0;
}

double Ruler::first_mark_val() const
{
    if (m_scroll) {
        double flag = (start()/unit_per_mark()) - (int)(start()/unit_per_mark());

        if (flag > 0.000000000001) {
            return start() + (1-flag) * unit_per_mark();
        } else if(flag < -0.000000000001) {
            return start() - flag*unit_per_mark();
        }
    }
    return start();
}

int Ruler::first_mark(int step) const
{
    if (m_scroll) {
        int ret = (int)(qAbs(first_mark_val()/unit_per_mark())+0.5)%step;
        if ( (start() < stop() && first_mark_val() > 0 && ret > 0)
             || ( start() > stop() && first_mark_val() < 0 && ret > 0) ) {
            ret = step - ret;
        }
        return ret;
    }
    return 0;
}

double Ruler::pixel_per_mark() const
{
    if (m_scroll) {
        return m_pixelPerMark;
    }

    if (mark_position() == TOP
            || mark_position() == BOTTOM) {
        return 1.0 * width() / mark_qty();
    } else {
        return 1.0 * height() / mark_qty();
    }
}

int Ruler::mark_qty() const
{
    int qty = 0;
    if (mark_position() == TOP
            || mark_position() == BOTTOM) {
        qty = width() / m_pixelPerMark + 0.5;
    } else {
        qty = height() / m_pixelPerMark + 0.5;
    }

    if (m_scroll) {
        return qty;
    }

    if (qty >= 100) {
        qty = 100;
    } else if (qty >= 80) {
        qty = 80;
    } else if (qty >= 50) {
        qty = 50;
    } else if (qty >= 40) {
        qty = 40;
    } else {
        qty = 20;
    }

    return qty;
}

void Ruler::draw_mark(QPainter &painter, int step, int markHeight, bool showVal)
{
    double fstMarkPos = first_mark_position();
    double pixelPerMark = pixel_per_mark();

    /* draw mark */
    for (int i = first_mark(step); i <= mark_qty(); i += step) {
        painter.drawLine(fstMarkPos+i*pixelPerMark, 0,
                         fstMarkPos+i*pixelPerMark, markHeight);
    }

    if (showVal) {
        /* draw text */
        painter.drawText(fstMarkPos + first_mark(step)*pixelPerMark + 1, markHeight - 2,
                         QString::number(first_mark_val() + first_mark(step)*unit_per_mark(), 'f', m_prec)+" "+m_unitStr);

        for (int i = first_mark(step)+step; i <= mark_qty(); i += step) {
            painter.drawText(fstMarkPos + i*pixelPerMark + 1, markHeight - 2,
                             QString::number(first_mark_val() + i*unit_per_mark(), 'f', m_prec));
        }
    }
}
