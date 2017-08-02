#ifndef __A_SCAN_H__
#define __A_SCAN_H__

#include <QColor>
#include <QSharedPointer>

namespace DplDisplay {

class Ascan : public QObject
{
    Q_OBJECT
public:
    explicit Ascan(QObject *parent = 0);

    /**
     * @brief color 获取波形颜色
     * @return      颜色
     */
    const QColor &color() const;

    /**
     * @brief set_color 设置波形颜色
     * @param color     颜色
     */
    void set_color(const QColor &color);

signals:
    void color_changed(const QColor &color);

public slots:

private:
    QColor m_color;
};

typedef QSharedPointer<Ascan> AscanPointer;

inline const QColor &Ascan::color() const
{
    return m_color;
}

inline void Ascan::set_color(const QColor &color)
{
    if (color != m_color) {
        m_color = color;
        emit color_changed(m_color);
    }
}

}
#endif // __A_SCAN_H__
