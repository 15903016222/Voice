#include "base_cursor_item.h"

#include <QPainter>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QString>

const int BaseCursorItem::s_defaultTooltipWidth     = 25;
const int BaseCursorItem::s_defaultTooltipHeight    = 13;

BaseCursorItem::BaseCursorItem(Qt::Orientation cursorOrientation,
                               E_CURSOR_TYPE cursorType,
                               E_CURSOR_SOURCE_TYPE sourceType,
                               const DplMeasure::CursorPointer &cursorPointer,
                               QGraphicsItem *parent) :
    QGraphicsObject(parent),
    m_cursorOrientation(cursorOrientation),
    m_cursorType(cursorType),
    m_sourceType(sourceType),
    m_movingFlag(false),
    m_visible(false),
    m_cursorPointer(cursorPointer)
{
    if(cursorType == BaseCursorItem::Reference) {
        m_color = QColor(Qt::blue);
    } else {
        m_color = QColor(Qt::red);
    }

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setZValue(1);
    setVisible(m_visible);

    init_update_pos();

}

QRectF BaseCursorItem::boundingRect() const
{
    if(Qt::Horizontal == m_cursorOrientation) {
        return QRectF(-m_size.width() / 2.0, -m_size.height() / 2.0,
                      m_size.width(), BaseCursorItem::s_defaultTooltipWidth);
    } else {
        return QRectF(-m_size.width() / 2.0, -m_size.height() / 2.0,
                      BaseCursorItem::s_defaultTooltipWidth, m_size.height());
    }
}

void BaseCursorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    paint_cursor(painter);
}

void BaseCursorItem::do_visible_changed(bool flag)
{
    setVisible(flag);
}


void BaseCursorItem::do_amplitude_reference_changed(double value)
{
    if(m_movingFlag) {
        return;
    }

    if (scene() && !scene()->views().isEmpty()) {
//        setPos(scene()->sceneRect().left() + (m_gate->start() - m_sample->start()  + m_offset )* ratio(),
//               scene()->sceneRect().bottom() - scene()->sceneRect().height() * m_gate->height() / 100);
    }
    update();
}

void BaseCursorItem::do_amplitude_measurement_changed(double value)
{
    update();
}

void BaseCursorItem::do_ultrasound_reference_changed(double value)
{
    update();
}

void BaseCursorItem::do_ultrasound_measurement_changed(double value)
{
    update();
}

void BaseCursorItem::do_scan_reference_changed(double value)
{
    if(m_movingFlag) {
        return;
    }

    if (scene() && !scene()->views().isEmpty()) {

    }
    update();
}

void BaseCursorItem::do_scan_measurement_changed(double value)
{
    update();
}

void BaseCursorItem::do_index_reference_changed(double value)
{
    update();
}

void BaseCursorItem::do_index_measurement_changed(double value)
{
    update();
}


void BaseCursorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = true;
    QGraphicsItem::mousePressEvent(event);
}

void BaseCursorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_movingFlag = false;
    QGraphicsItem::mouseReleaseEvent(event);
}

QVariant BaseCursorItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange && scene() && m_movingFlag) {
        QPointF newPos = value.toPointF();
        QRectF rect = scene()->sceneRect();

        if(!rect.contains(newPos)) {
            // Keep the item inside the scene rect.
            newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
            newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
        }

        if(m_cursorOrientation == Qt::Vertical) {
            newPos.setY(0.0);
        } else {
            newPos.setX(0.0);
        }

        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}


void BaseCursorItem::get_value(QString &valueText)
{
    double value;
    if(Reference == m_cursorType) {
        if(BaseCursorItem::Amplitude == m_sourceType) {
            value = m_cursorPointer->amplitude_reference();
        } else if(BaseCursorItem::Scan == m_sourceType) {
            value = m_cursorPointer->scan_reference();
        } else if(BaseCursorItem::Index == m_sourceType) {
            value = m_cursorPointer->index_reference();
        } else if(BaseCursorItem::Ultrasound == m_sourceType) {
            value = m_cursorPointer->ultrasound_reference();
        }
    } else {
        if(BaseCursorItem::Amplitude == m_sourceType) {
            value = m_cursorPointer->amplitude_measurement();
        } else if(BaseCursorItem::Scan == m_sourceType) {
            value = m_cursorPointer->scan_measurement();
        } else if(BaseCursorItem::Index == m_sourceType) {
            value = m_cursorPointer->index_measurement();
        } else if(BaseCursorItem::Ultrasound == m_sourceType) {
            value = m_cursorPointer->ultrasound_measurement();
        }
    }

    qDebug() << " value = " << value;

    valueText = QString::number(value, 'f', 2);
}

void BaseCursorItem::init_update_pos()
{
    if(Reference == m_cursorType) {
        if(BaseCursorItem::Amplitude == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(amplitude_reference_changed(double)),
                    this, SLOT(do_amplitude_reference_changed(double)));
        } else if(BaseCursorItem::Scan == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(scan_reference_changed(double)),
                    this, SLOT(do_scan_reference_changed(double)));
        } else if(BaseCursorItem::Index == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(index_reference_changed(double)),
                    this, SLOT(do_index_reference_changed(double)));
        } else if(BaseCursorItem::Ultrasound == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(ultrasound_reference_changed(double)),
                    this, SLOT(do_ultrasound_reference_changed(double)));
        }
    } else {
        if(BaseCursorItem::Amplitude == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(amplitude_measurement_changed(double)),
                    this, SLOT(do_amplitude_measurement_changed(double)));
        } else if(BaseCursorItem::Scan == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(scan_measurement_changed(double)),
                    this, SLOT(do_scan_measurement_changed(double)));
        } else if(BaseCursorItem::Index == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(index_measurement_changed(double)),
                    this, SLOT(do_index_measurement_changed(double)));
        } else if(BaseCursorItem::Ultrasound == m_sourceType) {
            connect(static_cast<DplMeasure::Cursor*>(m_cursorPointer.data()), SIGNAL(ultrasound_measurement_changed(double)),
                    this, SLOT(do_ultrasound_measurement_changed(double)));
        }
    }
}

