#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "a_scan.h"
#include "palette_color.h"

namespace DplDisplay {

class Display : public QObject
{
    Q_OBJECT
public:
    explicit Display(QObject *parent = 0);

    enum Layout {
        /* One Group */
        A       = 100,
        S,
        C,
        AS,
        SC,
        AB,
        ABC,
        ASB,
        ASC,
        /* Two Group */
        A2      = 200,
        S2,
        C2,
        AS2,
        ASC2,
        SC_AB,
        AB2,
        SC2,
        ABC2,
        ASB2,
        /* Three Group */
        A3      = 300,
        S3,
        C3,
        S_B_B,
        AS3,
        SC3,
        SC_AB2,
        S_S_B,
        SC2_AB,
        ASC3,
        ABS3,
        ABC3,
        /* Four Group */
        A4      = 400,
        S4,
        C4,
        AS4,
        SC4,
        SC3_AB,
        SC_AB2_SC,
        S2_B2,
        /* Five Group */
        A5      = 500,
        S4_B,
        S3_B2,
        /* Six Group */
        A6      = 600,
        S4_B2,
        /* Seven Group */
        A7      = 700,
        /* Eight */
        A8      = 800,
        /* A FFT */
        AFFT
    };

    /**
     * @brief layout    获取布局模式
     * @return          布局模式
     */
    Layout layout() const;

    /**
     * @brief set_layout    设置布局模式
     * @param layout        布局模式
     */
    void set_layout(Layout layout, const QVector<int> &grps);

    /**
     * @brief grps  获取显示组数
     * @return      显示的组数
     */
    const QVector<int> &grps() const;

    /**
     * @brief ascan 获取Ascan
     * @return      Ascan
     */
    const DplDisplay::AscanPointer &ascan() const;

    /**
     * @brief palette   获取PaletteColor
     * @return          PaletteColor
     */
    const PaletteColorPointer &palette() const;

signals:
    void layout_changed(DplDisplay::Display::Layout layout, const QVector<int> grps);

public slots:

private:
    Layout m_layout;
    QVector<int> m_grps;
    AscanPointer m_ascan;
    PaletteColorPointer m_palette;
};

typedef QSharedPointer<Display> DisplayPointer;

inline Display::Layout Display::layout() const
{
    return m_layout;
}

inline void Display::set_layout(Display::Layout layout,
                                const QVector<int> &grps)
{
    if (m_layout != layout || m_grps != grps) {
        m_layout = layout;
        m_grps = grps;
        emit layout_changed(m_layout, m_grps);
    }
}

inline const QVector<int> &Display::grps() const
{
    return m_grps;
}

inline const AscanPointer &Display::ascan() const
{
    return m_ascan;
}

inline const PaletteColorPointer &Display::palette() const
{
    return m_palette;
}

}
#endif // __DISPLAY_H__
