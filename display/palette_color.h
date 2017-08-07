#ifndef __PALETTE_COLOR_H__
#define __PALETTE_COLOR_H__

#include <QSharedPointer>
#include <QVector>
#include <QColor>

class QXmlStreamReader;
typedef QSharedPointer<QColor> QColorPointer;

namespace DplDisplay {

class PaletteColor : public QObject
{
    Q_OBJECT
public:
    PaletteColor(QObject *parent = 0);

    /**
     * @brief load  加载读取调色板颜色文件
     * @param path  文件路径名
     * @return      成功返回true，失败返回false
     */
    bool load(const QString &path);

    /**
     * @brief color 获取位置(幅值)颜色
     * @param index 位置（幅值)
     * @return      颜色
     */
    QColorPointer color(quint8 index) const;

    /**
     * @brief size  获取调色板颜色数量
     * @return      数量
     */
    int size() const;

    quint32 pixmap(quint8 index) const;

signals:
    void changed();

protected:
    void read_special_colors(QXmlStreamReader &xml);

    void read_main_colors(QXmlStreamReader &xml);

private:
    QVector<QColorPointer> m_colorVector;
};

typedef QSharedPointer<PaletteColor> PaletteColorPointer;

inline QColorPointer PaletteColor::color(quint8 index) const
{
    if (index < m_colorVector.size()) {
        return m_colorVector[index];
    } else {
        return QColorPointer(new QColor(Qt::black));
    }
}

inline int PaletteColor::size() const
{
    return m_colorVector.size();
}

inline quint32 PaletteColor::pixmap(quint8 index) const
{
    return color(index)->rgb();
}

}
#endif // __PALETTE_COLOR_H__
