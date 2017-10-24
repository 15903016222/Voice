#ifndef __BASE_CURSOR_ITEM_H__
#define __BASE_CURSOR_ITEM_H__

#include <QGraphicsItem>
#include <device/device.h>
#include <mcu/mcu.h>


class BaseCursorItem : public QGraphicsObject
{
    Q_OBJECT
public:

    enum E_CURSOR_TYPE {
        REFERENCE,
        MEASUREMENT
    };

    enum E_CURSOR_SOURCE_TYPE {
        Amplitude,          /* 幅度 */
        Scan,               /* 扫查轴 */
        Index,              /* 步进轴 */
        Ultrasound          /* 超声轴 */
    };


    explicit BaseCursorItem(Qt::Orientation cursorOrientation,
                            const DplDevice::GroupPointer &group,
                            E_CURSOR_TYPE cursorType,
                            E_CURSOR_SOURCE_TYPE sourceType,
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
    void update_pos(float value);
    void do_mcu_key_event(Mcu::KeyType type);

protected:

    Qt::Orientation         m_cursorOrientation;
    DplDevice::GroupPointer m_group;
    E_CURSOR_SOURCE_TYPE    m_sourceType;
    QSize   m_size;
    QColor  m_color;
    volatile bool m_movingFlag;
    volatile bool m_visible;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void paint_cursor(QPainter *painter) = 0;
    void get_value(QString &valueText);

private:
    void init_update_pos();
};

class VScanCursorItem : public BaseCursorItem
{
public:
    explicit VScanCursorItem(Qt::Orientation cursorOrientation,
                    const DplDevice::GroupPointer &group,
                    E_CURSOR_TYPE cursorType,
                    E_CURSOR_SOURCE_TYPE sourceType,
                    QGraphicsItem *parent = 0);
protected:
    virtual void paint_cursor(QPainter *painter);
};


class HScanCursorItem : public BaseCursorItem
{
public:
    explicit HScanCursorItem(Qt::Orientation cursorOrientation,
                    const DplDevice::GroupPointer &group,
                    E_CURSOR_TYPE cursorType,
                    E_CURSOR_SOURCE_TYPE sourceType,
                    QGraphicsItem *parent = 0);
protected:
    virtual void paint_cursor(QPainter *painter);
};



#endif // __BASE_CURSOR_ITEM_H__
