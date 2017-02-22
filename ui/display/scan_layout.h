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
        A,
        S,
        C,
        AS,
        SC,
        AB,
        ABC,
        ASB,
        ASC,
        /* Two Group */
        A2,
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
        A3,
        S3,
        C3,

        ASC3,
        AS3,
        MAX_MODE
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
