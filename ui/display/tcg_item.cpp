#include "tcg_item.h"
#include <QPainter>

TcgItem::TcgItem(const DplSizing::TcgsPointer &tcgs, const DplUt::SamplePointer &sample, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_tcgs(tcgs),
    m_sample(sample),
    m_size(400, 200)
{
//    connect(static_cast<DplSizing::Tcgs *>(m_tcgs.data()),
//            SIGNAL(changed()),
//            )
    connect(static_cast<DplSizing::Tcgs *>(m_tcgs.data()),
            SIGNAL(enabled_changed(bool)),
            this,
            SLOT(set_visible(bool)));
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

    float xRatio = m_size.width() / m_sample->range();
    float yRatio = m_size.height() / 100.0;
    float sampleStart = m_sample->start();

    int pointQty = m_tcgs->point_count();

    DplSizing::TcgPointer tcg = m_tcgs->current_tcg();

    /* draw lines */
    painter->setPen(Qt::darkGreen);
    for (int i = 0; i < pointQty-1; ++i) {
        painter->drawLine(xRatio*(tcg->position(i)-sampleStart)+3,
                          m_size.height() - yRatio * tcg->amplitude(i) - 3,
                          xRatio*(tcg->position(i+1)-sampleStart)+3,
                          m_size.height() - yRatio * tcg->amplitude(i+1) - 3);
    }

    /* draw points */
    painter->setPen(Qt::transparent);
    painter->setBrush(Qt::gray);
    for (int i = 0; i < pointQty; ++i) {
        painter->drawRect(xRatio*(tcg->position(i)-sampleStart),
                          m_size.height() - yRatio*tcg->amplitude(i) - 5,
                          6,
                          6);
    }
    painter->setBrush(Qt::red);
    painter->drawRect(xRatio*(m_tcgs->position()-sampleStart),
                      m_size.height() - yRatio*m_tcgs->amplitude() - 5,
                      6,
                      6);
}

void TcgItem::set_visible(bool flag)
{
    setVisible(flag);
}
