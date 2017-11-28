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

    /**
     * @brief enable    获取工作状态
     * @return          开启返回true,关闭返回false
     */
    bool enable() const;

    /**
     * @brief set_enable    设置工作状态
     * @param flag          true为开启,false为关闭
     * @return              设置成功返回true, 否则为false
     */
    bool set_enable(bool flag);

    /**
     * @brief logic_group   获取作用的逻辑组
     * @return              逻辑组
     */
    quint16 logic_group() const;

    /**
     * @brief set_logic_group   设置作用的逻辑组
     * @param groups            逻辑组
     * @return                  设置成功返回true,失败返回false
     */
    bool set_logic_group(quint16 groups);

    /**
     * @brief The Type enum 模拟输出类型
     */
    enum Type {
        NONE         = 0b000,                        /* 无效类型 */
        GATE_A       = 0b001,                        /* A闸门峰值 */
        GATE_B       = 0b010,                        /* B闸门峰值 */
        THICKNESS    = 0b100                         /* 厚度 */
    };

    /**
     * @brief type  获取模拟输出类型
     * @return      类型
     */
    Type type() const;

    /**
     * @brief set_type  设置模拟输出类型
     * @param type      类型
     * @return          设置成功返回true,失败返回false
     */
    bool set_type(Type type);

private:
    FpgaPrivate *m_fpgaPrvate;
    int m_index;
};

}
#endif // __DPLFPGA_ALARM_ANALOG_H__
