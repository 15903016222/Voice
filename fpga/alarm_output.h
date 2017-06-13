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

    bool is_valid() const;
    bool set_valid(bool flag);

    quint16 logic_group() const;
    bool set_logic_group(quint16 groups);

    enum Operator {
        AND,
        OR
    };
    Operator op(void);
    bool set_op(Operator op);

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
    Condition condition(int index);
    bool set_condition(int index, Condition cond);

    quint32 count() const;
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

private:
    FpgaPrivate *m_fpgaPrivate;
    int m_index;
};

}
#endif // __DPLFPGA_ALARM_OUTPUT_H__
