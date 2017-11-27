#ifndef __DPLFPGA_TCG_H__
#define __DPLFPGA_TCG_H__

#include "fpga_global.h"
#include <QSharedPointer>

namespace DplFpga {

class TcgPrivate;
class FPGASHARED_EXPORT Tcg
{
public:
    static const int MAX_POINTS = 16;

    explicit Tcg(const int index = 0);
    ~Tcg();

    /**
     * @brief index 获取TCG序号
     * @return      序号(从0开始)
     */
    int index(void) const;

    /**
     * @brief set_index 设置TCG序号
     * @param index     序号(从0开始)
     */
    void set_index(int index);

    /**
     * @brief tcg_position 获取指定TCG点的位置
     * @param point        点索引号(范围 0 ~ MAX_POINTS-1)
     * @return             返回指定点的位置(ns)
     */
    int position(int point) const;

    /**
     * @brief set_tcg_position 设置对应TCG点的位置
     * @param point            点索引号(范围 0 ~ MAX_POINTS-1)
     * @param pos              位置值(ns)
     * @return                 成功返回true，失败返回false
     */
    bool set_position(int point, int pos);

    /**
     * @brief gain  获取指定点增益
     * @param point 点索引号(范围 0 ~ MAX_POINTS-1)
     * @return      增益(dB)
     */
    float gain(int point) const;

    /**
     * @brief set_gain  设置指定点增益
     * @param point     点索引号(范围 0 ~ MAX_POINTS-1)
     * @param gain      增益(dB)
     * @return          成功返回true,失败返回false
     */
    bool set_gain(int point, float gain);

    /**
     * @brief deploy    下发配置
     * @return          成功返回true,失败返回false
     */
    bool deploy() const;

private:
    TcgPrivate *d;
};

typedef QSharedPointer<Tcg> TcgPointer;

}

#endif // __DPLFPGA_TCG_H__
