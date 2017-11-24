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

    struct S_CURSOR_INFO {
        double start;
        double end;
        double currentValue;
        double pos;
    };

    explicit BaseCursorItem(Qt::Orientation cursorOrientation,
                            E_CURSOR_TYPE cursorType,
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
     * @brief set_size  设置光标的size
     * @param size  宽高值
     */
    inline void set_size(const QSize size) { m_size = size; }


    /**
     * @brief set_cursor_info   设置光标信息
     * @param cursorInfo        光标信息
     */
    void set_cursor_info(const S_CURSOR_INFO &cursorInfo);

signals:
    void value_changed(double value);

protected slots:
    /**
     * @brief do_visible_changed    处理光标的显示/隐藏变化
     * @param flag  true：显示； false：隐藏
     */
    void do_visible_changed(bool flag);

protected:

    Qt::Orientation         m_cursorOrientation;
    E_CURSOR_TYPE           m_cursorType;
    QSize   m_size;
    QColor  m_color;
    volatile bool m_movingFlag;
    volatile bool m_visible;
    S_CURSOR_INFO m_cursorInfo;

    static const int    s_defaultTooltipWidth;
    static const int    s_defaultTooltipHeight;

    /**
     * @brief mousePressEvent   鼠标按下事件处理
     * @param event             事件
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mouseReleaseEvent 释放鼠标事件处理
     * @param event             事件
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief itemChange    图元改变事件处理
     * @param change        改变类型
     * @param value         改变数值
     * @return
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    /**
     * @brief paint_cursor  画光标
     * @param painter
     */
    virtual void paint_cursor(QPainter *painter) = 0;

    /**
     * @brief get_value 获取显示值
     * @param valueText 保存显示值的字符串
     */
    void get_value(QString &valueText);

};

#endif // __BASE_CURSOR_ITEM_H__
