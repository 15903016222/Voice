#ifndef __SCAN_LAYOUT_H__
#define __SCAN_LAYOUT_H__

#include <QWidget>

class ScanLayout : public QWidget
{
    Q_OBJECT
public:
    explicit ScanLayout(QWidget *parent = 0);

    enum Mode {
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
    };

    /**
     * @brief set_mode  设置布局模式
     * @param mode      模式
     * @param grpIds    组ID列表
     */
    void set_mode(Mode mode, const QList<int> &grpIds);

    /**
     * @brief get_groups_id 获取组ID列表
     * @return              组ID列表
     */
    const QList<int> &get_groups_id() const { return m_grpIds; }

private:
    Mode m_mode;
    QList<int> m_grpIds;

    void a_layout();
};

#endif // __SCAN_LAYOUT_H__
