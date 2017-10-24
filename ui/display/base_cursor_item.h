#ifndef __BASE_CURSOR_ITEM_H__
#define __BASE_CURSOR_ITEM_H__

#include <QGraphicsItem>
#include <device/device.h>
#include <measure/cursor.h>

class BaseCursorItem : public QGraphicsObject
{
    Q_OBJECT
public:

    enum E_CURSOR_TYPE {
        Reference,
        Measurement
    };

    enum E_CURSOR_SOURCE_TYPE {
        Amplitude,          /* 幅度 */
        Scan,               /* 扫查轴 */
        Index,              /* 步进轴 */
        Ultrasound          /* 超声轴 */
    };


    explicit BaseCursorItem(Qt::Orientation cursorOrientation,
                            E_CURSOR_TYPE cursorType,
                            E_CURSOR_SOURCE_TYPE sourceType,
                            const DplMeasure::CursorPointer &cursorPointer,
                            QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    /**
     * @brief paint
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief set_size
     * @param size
     */
    inline void set_size(const QSize size) { m_size = size; }

signals:
    void visible_changed(bool flag);

protected slots:
    void do_visible_changed(bool flag);

    void do_amplitude_reference_changed(double value);
    void do_amplitude_measurement_changed(double value);
    void do_ultrasound_reference_changed(double value);
    void do_ultrasound_measurement_changed(double value);
    void do_scan_reference_changed(double value);
    void do_scan_measurement_changed(double value);
    void do_index_reference_changed(double value);
    void do_index_measurement_changed(double value);

protected:

    Qt::Orientation         m_cursorOrientation;
    E_CURSOR_TYPE           m_cursorType;
    E_CURSOR_SOURCE_TYPE    m_sourceType;
    QSize   m_size;
    QColor  m_color;
    volatile bool m_movingFlag;
    volatile bool m_visible;
    DplMeasure::CursorPointer   m_cursorPointer;

    static const int    s_defaultTooltipWidth;
    static const int    s_defaultTooltipHeight;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void paint_cursor(QPainter *painter) = 0;
    void get_value(QString &valueText);

private:
    void init_update_pos();
};

#endif // __BASE_CURSOR_ITEM_H__
