#ifndef __FFT_MENU_H__
#define __FFT_MENU_H__

#include "../base_menu.h"
#include <device/group.h>

namespace DplProbeMenu {

class FftMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FftMenu(QWidget *parent);
    ~FftMenu();

private slots:
    /**
     * @brief do_switchItem_changed 处理FFT开关处理
     * @param val   当前index：0=开启，1=关闭
     */
    void do_switchItem_changed(int val);

    /**
     * @brief do_current_group_changed  处理当前组响应
     * @param groupPointer              当前组
     */
    void do_current_group_changed(const DplDevice::GroupPointer &groupPointer);

    /**
     * @brief do_start_changed  处理Gate A的起始点变化
     * @param val               当前起始点值
     */
    void do_start_changed(float val);

    /**
     * @brief do_width_changed  处理Gate A的宽度变化
     * @param val               当前宽度值
     */
    void do_width_changed(float val);

    /**
     * @brief do_startItem_value_changed  处理闸门A开始item的数值变化
     * @param val                         当前Gate A的起始值
     */
    void do_startItem_value_changed(double val);

    /**
     * @brief do_widthItem_value_changed    处理闸门A宽度item的数值变化
     * @param val                           当前Gate A的宽度
     */
    void do_widthItem_value_changed(double val);

    /**
     * @brief do_gainItem_changed   处理GainItem数值变化
     * @param gain                  变化的Gain数值
     */
    void do_gainItem_changed(double gain);

    /**
     * @brief do_gain_changed 处理Gain类数值变化
     * @param val             变化的Gain值
     */
    void do_gain_changed(float val);

private:
    SpinMenuItem *m_gainItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_widthItem;
    ComboMenuItem *m_switchItem;

    void init_connection();
    DplDevice::GroupPointer m_currentGroupPointer;

};

}
#endif // __FFT_MENU_H__
