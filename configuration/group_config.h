/**
 * @file    group_config.h
 * @brief   组配置信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __GROUP_CONFIG_H__
#define __GROUP_CONFIG_H__

#include "base_item_config.h"

#include <device/device.h>
#include <device/group.h>

namespace Config {

class GroupConfig : public BaseItemConfig
{
public:
    GroupConfig(msgpack::packer<msgpack::sbuffer> *packer);

    /**
     * @brief pack 配置文件打包
     */
    virtual void pack();

    /**
     * @brief unpack    解包配置文件
     * @param obj       待解包的对象
     * @return
     */
    virtual bool unpack(const msgpack::v2::object &obj);

private:

    /**
     * @brief pack_group_child_item_config  打包组里的子项
     * @param groupPointer                  当前组的指针
     */
    void pack_group_child_item_config(const DplDevice::GroupPointer &groupPointer);

    /**
     * @brief pack_group_*_config  打包组里的子项，包括：general、gate、UT、focallawer、DAC、TCG、cursor、scan
     * @param groupPointer         当前组的指针
     */
    void pack_group_general_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_gate_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_ut_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_focallawer_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_dacs_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_tcgs_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_cursor_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_scan_config(const DplDevice::GroupPointer &groupPointer);

    /**
     * @brief pack_gate_config  打包闸门信息
     * @param groupPointer      当前组指针
     * @param type              闸门类型
     */
    void pack_gate_config(const DplDevice::GroupPointer &groupPointer, DplFpga::Group::GateType type);

    /**
     * @brief pack_ut_*_config  打包UT的子项，包括：sample、transceiver
     * @param groupPointer      当前组的指针
     */
    void pack_ut_sample_config(const DplDevice::GroupPointer &groupPointer);
    void pack_ut_transceiver_config(const DplDevice::GroupPointer &groupPointer);

    /**
     * @brief pack_focallawer_*_config  打包focallawer的子项，包括：probe、wedge、specimen、focusCnf
     * @param groupPointer              当前组的指针
     */
    void pack_focallawer_probe_config(const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_wedge_config(const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_specimen_config(const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_focusCnf_config(const DplDevice::GroupPointer &groupPointer);

    /**
     * @brief unpack_group_item_config  解包组的子项
     * @param key                       子项关键字
     * @param item                      内容
     */
    void unpack_group_item_config(int key, msgpack::object &item);

    /**
     * @brief unpack_group_*_config     解包组内的各子项：包括general、gate、UT、focallawer、DAC、TCG、cursor、scan
     * @param item                      保存子项的对象
     */
    void unpack_group_general_config(msgpack::object &item);
    void unpack_group_gate_config(msgpack::object &item);
    void unpack_group_ut_config(msgpack::object &item);
    void unpack_group_focallawer_config(msgpack::object&item);
    void unpack_group_dacs_config(msgpack::object &item);
    void unpack_group_tcgs_config(msgpack::object &item);
    void unpack_group_scan_config(msgpack::object &item);
    void unpack_group_cursor_config(msgpack::object&item);

    /**
     * @brief unpack_gate_config    解包闸门信息
     * @param obj                   保存子项的对象
     */
    void unpack_gate_config(msgpack::object &obj);

    /**
     * @brief unpack_sampe_config    解包采样率信息
     * @param obj                    保存子项的对象
     */
    void unpack_sampe_config(const msgpack::object &obj);

    /**
     * @brief unpack_transceiver_config     解包transceiver信息
     * @param obj                           保存子项的对象
     */
    void unpack_transceiver_config(const msgpack::object &obj);

    /**
     * @brief unpack_focallawer_*_config    解包focallawer的子项，包括：probe、wedge、specimen、focusCnf
     * @param obj                           保存子项的对象
     */
    void unpack_focallawer_probe_config(const msgpack::object &obj);
    void unpack_focallawer_wedge_config(const msgpack::object &obj);
    void unpack_focallawer_specimen_config(const msgpack::object &obj);
    void unpack_focallawer_focusCnf_config(const msgpack::object &obj);

    /**
     * @brief set_tcg_points    设置TCG点属性
     * @param tcgs              当前TCG
     * @param points            保存点信息的对象
     * @param arraySize         点的总数
     */
    void set_tcg_points(DplSizing::TcgsPointer &tcgs, msgpack::object *points, int arraySize);

    DplDevice::GroupPointer m_groupPointer;
};

}

#endif // GROUPCONFIG_H
