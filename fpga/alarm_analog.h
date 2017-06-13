/**
 * @file alarm_analog.h
 * @brief AlarmAnalog
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-05-03
 */
#ifndef __DPLFPGA_ALARM_ANALOG_H__
#define __DPLFPGA_ALARM_ANALOG_H__

#include "fpga_global.h"

namespace DplFpga {

class FpgaPrivate;
class FPGASHARED_EXPORT AlarmAnalog
{
public:
    AlarmAnalog(FpgaPrivate *fpgaPrivate, int index);

    bool is_valid() const;
    bool set_valid(bool flag);

    quint16 logic_group() const;
    bool set_logic_group(quint16 groups);

    enum Type {
        NONE         = 0b000,                        /* 无效类型 */
        GATE_A       = 0b001,                        /* A闸门峰值 */
        GATE_B       = 0b010,                        /* B闸门峰值 */
        THICKNESS    = 0b100                         /* 厚度 */
    };
    Type type() const;
    bool set_type(Type type);

private:
    FpgaPrivate *m_fpgaPrvate;
    int m_index;
};

}
#endif // __DPLFPGA_ALARM_ANALOG_H__
