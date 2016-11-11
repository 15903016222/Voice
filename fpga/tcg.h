#ifndef __TCG_H__
#define __TCG_H__

#include <QObject>

struct TcgData;

class Tcg
{
public:
    static const int MAX_POINTS;

    explicit Tcg(const int index = 0);
    ~Tcg();

    int index(void) const { return m_index; }

    /**
     * @brief tcg_position 返回对应TCG点的位置
     * @param point        指定TCG点, 最大值为 (MAX_POINTS-1)
     * @return             成功返回指定点的位置,单位为ns
     */
    quint32 tcg_position(quint32 point) const;

    /**
     * @brief set_tcg_position 设置对应TCG点的位置
     * @param point            指定TCG点，最大值为 (MAX_POINTS-1)
     * @param val              要设置的TCG点的位置值
     * @return                 成功返回true，失败返回false
     */
    bool set_tcg_position(quint32 point, quint32 val);

    /**
     * @brief tcg_slope 返回对应TCG点的前一点斜率
     * @param point     指定TCG点
     * @return          返回指定点的前一点斜率，如果指定点为0，则返回0
     */
    quint32 tcg_slope(quint32 point) const;

    /**
     * @brief set_tcg_slope 设置指定点的前一点斜率
     * @param point         指定TCG点
     * @param val           指定点的前一点斜率
     * @return              成功返加true，失败返回false
     */
    bool set_tcg_slope(quint32 point, quint32 val) ;

    bool tcg_flag(quint32 point) const;
    bool set_tcg_flag(quint32 point, bool flag);

    bool reflesh() const;
private:
    int m_index;
    TcgData *d;
};

#endif // TCG_H
