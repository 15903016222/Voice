#ifndef __PALETTE_COLOR_H__
#define __PALETTE_COLOR_H__

#include <QSharedPointer>
#include <QVector>
#include <QColor>

class QXmlStreamReader;

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
    QColor color(quint8 index) const;

    /**
     * @brief colors    获取颜色向量表
     * @return          向量表
     */
    const QVector<QRgb> &colors() const;

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
    QVector<QRgb> m_colors;
};

typedef QSharedPointer<PaletteColor> PaletteColorPointer;

inline QColor PaletteColor::color(quint8 index) const
{
    return QColor(m_colors[index]);
}

inline const QVector<QRgb> &PaletteColor::colors() const
{
    return m_colors;
}

inline int PaletteColor::size() const
{
    return m_colors.size();
}

inline quint32 PaletteColor::pixmap(quint8 index) const
{
    return m_colors[index];
}

}
#endif // __PALETTE_COLOR_H__
