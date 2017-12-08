/**
 * @file dacs.h
 * @brief DAC(Distance Amplitude Correction)组
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-12-07
 */
#ifndef __DPLSIZING_DACS_H__
#define __DPLSIZING_DACS_H__

#include "dac.h"

namespace DplSizing {

class DacsPrivate;
class Dacs : public QObject
{
    Q_OBJECT
public:
    explicit Dacs(QObject *parent);

    /**
     * @brief enabled   获取使能状态
     * @return          true为开启，false为关闭
     */
    bool enabled() const;

    /**
     * @brief set_enabled   设置使能状态
     * @param flag          true为开启，false为关闭
     */
    void set_enabled(bool flag);

    /**
     * @brief reference_amplitude   获取参考幅度
     * @return                      幅度(%)
     */
    float reference_amplitude() const;

    /**
     * @brief set_reference_amplitude   设置参考幅度
     * @param val                       幅度(%)
     * @return                          成功返回treu,失败返回false
     */
    bool set_reference_amplitude(float val);

    /**
     * @brief reference_gain    获取参考幅度增益补偿
     * @return                  增益(dB)
     */
    float reference_gain() const;

    /**
     * @brief set_reference_gain    设置参考幅度增益补偿
     * @param gain                  增益(dB)
     * @return                      设置成功返回true,失败返回false
     */
    bool set_reference_gain(float gain);

    /**
     * @brief step  获取曲线增益差
     * @return      增益差(dB)
     */
    float step() const;

    /**
     * @brief set_step  设置曲线增益差
     * @param val       增益差(dB)
     * @return
     */
    bool set_step(float val) const;

    /**
     * @brief current_dac   获取当前Dac
     * @return              Dac对象
     */
    DacPointer current_dac() const;

    /**
     * @brief current_dac_index 获取当前Dac索引号
     * @return                  索引号（从0开始）
     */
    int current_dac_index() const;

    /**
     * @brief set_current_dac   设置当前Dac
     * @param index             索引号
     * @return                  设置成功返回true,失败返回false
     */
    bool set_current_dac(int index);

    /**
     * @brief current_point 获取当前点索引号
     * @return              索引号(从0开始)
     */
    int current_point() const;

    /**
     * @brief current_position  获取当前Dac的当前点的位置
     * @return                  位置(ns)
     */
    float current_position() const;

    /**
     * @brief set_current_point 设置当前点的索引号
     * @param index             索引号(从0开始)
     * @return                  设置成功返回true,失败返回false
     */
    bool set_current_point(int index);

    /**
     * @brief add_point 添加点
     * @return          添加成功返回true,失败返回false
     */
    bool add_point();

    /**
     * @brief delete_point  删除点
     * @return              删除成功返回true,失败返回false
     */
    bool delete_point();

signals:
    void enabled_changed(bool flag);

public slots:

private:
    DacsPrivate *d;
};

}

#endif // __DPLSIZING_DACS_H__
