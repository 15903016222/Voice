#ifndef __TOOL_H__
#define __TOOL_H__

#include <device/group.h>

class Tool
{
public:
    /**
     * @brief cnf_to_display    配置数据转换成显示数据
     * @param group             组信息
     * @param val               数据(ns)
     * @return                  显示数据(us或mm)
     */
    static double cnf_to_display(const DplDevice::GroupPointer &group, double val);

    /**
     * @brief display_to_cnf    显示数据转换成配置数据
     * @param group             组信息
     * @param val               显示数据(us或mm)
     * @return                  配置数据(ns)
     */
    static double display_to_cnf(const DplDevice::GroupPointer &group, double val);

};   // end of Tool Class

#endif // __TOOL_H__

