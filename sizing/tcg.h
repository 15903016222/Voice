/**
 * @file tcg.h
 * @brief The Time-Corrected Gain
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-11-23 16:57
 */

#ifndef __DPLSIZING_TCG_H__
#define __DPLSIZING_TCG_H__

#include <QSharedPointer>

namespace DplSizing {

class TcgPrivate;
class Tcg
{
    friend class Tcgs;
    friend class TcgsPrivate;
public:
    explicit Tcg(int index);
    ~Tcg();

    /**
     * @brief index 获取序列号
     * @return      序列号(从0开始)
     */
    int index() const;

    /**
     * @brief position  获取指定点的位置
     * @param point     点索引号(从0开始)
     * @return          位置(ns)
     */
    int position(int point) const;

    /**
     * @brief gain      获取指定点的增益
     * @param point     点索引号(从0开始)
     * @return          位置(dB)
     */
    float gain(int point) const;

    /**
     * @brief amplitude 获取指定点的幅度
     * @param point     点索引号(从0开始)
     * @return          幅度(%)
     */
    float amplitude(int point) const;

    /**
     * @brief ref_amplitude 获取参考幅度
     * @return              幅度(%)
     */
    float ref_amplitude() const;

    /**
     * @brief set_ref_amplitude 设置参考幅度
     * @param refAmplitude      幅度(%)
     */
    void set_ref_amplitude(float refAmplitude) const;

protected:
    /**
     * @brief set_index 设置Tcg序列号
     * @param index     序列号(从0开始)
     */
    void set_index(int index);

    /**
     * @brief set_position  设置指定点的位置
     * @param point         点索引号(从0开始)
     * @param val           位置(ns)
     * @return              设置成功返回true,失败返回false
     */
    bool set_position(int point, int val);

    /**
     * @brief set_gain  设置指定点的增益
     * @param point     点索引号(从0开始)
     * @param val       增益(dB)
     * @return          设置成功返回true,失败返回false
     */
    bool set_gain(int point, float val);

    /**
     * @brief deploy    下发配置信息
     * @return          成功返回true,失败为false
     */
    bool deploy() const;

private:
    TcgPrivate *d;
};

typedef QSharedPointer<Tcg> TcgPointer;

}

#endif // end of __DPLSIZING_TCG_H__
