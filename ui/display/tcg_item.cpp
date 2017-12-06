#include "tcg_item.h"
#include <QPainter>

TcgItem::TcgItem(const DplSizing::TcgsPointer &tcgs, const DplUt::SamplePointer &sample, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_tcgs(tcgs),
    m_sample(sample),
    m_size(400, 200)
{
    connect(static_cast<DplSizing::Tcgs *>(m_tcgs.data()),
            SIGNAL(gain_changed()),
            this,
            SLOT(do_tcgs_changed()));
    connect(static_cast<DplSizing::Tcgs *>(m_tcgs.data()),
            SIGNAL(position_changed()),
            this,
            SLOT(do_tcgs_changed()));
    connect(static_cast<DplSizing::Tcgs *>(m_tcgs.data()),
            SIGNAL(enabled_changed(bool)),
            this,
            SLOT(set_visible(bool)));
    do_tcgs_changed();
    set_visible(m_tcgs->enable());
}

QRectF TcgItem::boundingRect() const
{
    return QRectF(-m_size.width()/2, -m_size.height()/2,
                  m_size.width(), m_size.height());
}

void TcgItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->translate(boundingRect().topLeft());

    /* draw lines */
    painter->setPen(Qt::darkGreen);
    painter->drawPath(m_linesPath);

    /* draw points */
    painter->setPen(Qt::transparent);
    painter->setBrush(Qt::gray);
    painter->drawPath(m_pointsPath);

    painter->setBrush(Qt::red);
    painter->drawRect(QRectF(x_ratio() * (m_tcgs->position()-m_sample->start()),
                      m_size.height() - y_ration() * m_tcgs->amplitude() - 5,
                      6,
                      6));
}

void TcgItem::set_visible(bool flag)
{
    setVisible(flag);
}

void TcgItem::do_tcgs_changed()
{
    m_linesPath = lines_path(m_tcgs->current_tcg());
    m_pointsPath = points_path(m_tcgs->current_tcg());
}

QPainterPath TcgItem::lines_path(const DplSizing::TcgPointer &tcg) const
{
    QPainterPath path;

    path.moveTo( x_ratio() * (tcg->position(0)-m_sample->start()) + 3,
                m_size.height() - 3);
    for (int i = 1; i < m_tcgs->point_count(); ++i) {
        path.lineTo( x_ratio() * (tcg->position(i)-m_sample->start()) + 3,
                    m_size.height() - y_ration() * tcg->amplitude(i) - 3);
    }

    return path;
}

QPainterPath TcgItem::points_path(const DplSizing::TcgPointer &tcg) const
{
    QPainterPath path;
    for (int i = 0; i < m_tcgs->point_count(); ++i) {
        path.addRect( x_ratio() * (tcg->position(i)-m_sample->start()),
                     m_size.height() - (y_ration() * tcg->amplitude(i)) - 5,
                     6, 6);
    }
    return path;
}
