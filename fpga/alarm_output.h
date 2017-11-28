/**
 * @file alarm_output.h
 * @brief 输出报警
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-05-03
 */

#ifndef __DPLFPGA_ALARM_OUTPUT_H__
#define __DPLFPGA_ALARM_OUTPUT_H__

#include "fpga_global.h"

namespace DplFpga {

class FpgaPrivate;
class FPGASHARED_EXPORT AlarmOutput
{
public:
    AlarmOutput(FpgaPrivate *fpgaPrivate, int index);

    /**
     * @brief enable    获取开启状态
     * @return          true为开启,false为关闭
     */
    bool enable() const;

    /**
     * @brief set_enable    设置开启状态
     * @param flag          true为开启,false为关闭
     * @return              设置成功返回true,否则为false
     */
    bool set_enable(bool flag);

    quint16 logic_group() const;
    bool set_logic_group(quint16 groups);

    /**
     * @brief The Operator enum 操作类型
     */
    enum Operator {
        AND,
        OR
    };

    /**
     * @brief op    获取操作类型
     * @return      操作类型
     */
    Operator op(void) const;

    /**
     * @brief set_op    设置操作类型
     * @param op        操作类型
     * @return          设置成功返回true,失败为false
     */
    bool set_op(Operator op);

    /**
     * @brief The Condition enum    报警条件类型
     */
    enum Condition {
        CONDITION_NONE,
        CONDITION_GATE_A        = 0b0001,
        CONDITION_GATE_B        = 0b0010,
        CONDITION_GATE_I        = 0b0011,
        CONDITION_NOT_GATE_A    = 0b0100,
        CONDITION_NOT_GATE_B    = 0b0101,
        CONDITION_NOT_GATE_I    = 0b0110,
        CONDITION_MAX_THICKNESS = 0b0111,
        CONDITION_MIN_THICKNESS = 0b1000
    };

    /**
     * @brief first_condition   获取报警条件1类型
     * @return                  条件类型
     */
    Condition first_condition() const;

    /**
     * @brief second_condition  获取报警条件2类型
     * @return                  条件类型
     */
    Condition second_condition() const;

    /**
     * @brief set_condition 设置报警条件类型
     * @param fstCond       条件1
     * @param sndCond       条件2
     * @return              设置成功返回true,失败返回false
     */
    bool set_condition(Condition fstCond, Condition sndCond);

    /**
     * @brief set_condition 设置报警条件类型
     * @param fstCond       条件1
     * @param op            操作类型
     * @param sndCond       条件2
     * @return              设置成功返回true,失败返回false
     */
    bool set_condition(Condition fstCond, Operator op, Condition sndCond);

    /**
     * @brief count 获取触发条件计数器
     * @return      数
     */
    quint32 count() const;

    /**
     * @brief set_count 设置触发条件计数器
     * @param count     数
     * @return          成功返回true,失败返回false
     */
    bool set_count(quint32 count);

    /**
     * @brief delay 获取延迟时间
     * @return      时间(us)
     */
    int delay() const;

    /**
     * @brief set_delay 设置延迟时间
     * @param delay     时间(us)
     * @return          成功返回true，否则false
     */
    bool set_delay(int delay);

    /**
     * @brief hold_time 获取保持时间
     * @return          时间(us)
     */
    int hold_time() const;

    /**
     * @brief set_hold_time 设置保持时间
     * @param time          时间(us)
     * @return              成功返回true，否则false
     */
    bool set_hold_time(int time);

    /**
     * @brief init  初始化配置信息
     */
    void init();

private:
    FpgaPrivate *m_fpgaPrivate;
    int m_index;
};

}
#endif // __DPLFPGA_ALARM_OUTPUT_H__
