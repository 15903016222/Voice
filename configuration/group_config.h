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

    virtual void pack();
    virtual void unpack(const msgpack::v2::object &obj);

private:

    void pack_group_child_item_config(const DplDevice::GroupPointer &groupPointer);

    MetaItem pack_gate_curves_config(const DplDevice::GroupPointer &groupPointer);
    MetaItem pack_ut_config(const DplDevice::GroupPointer &groupPointer);
    MetaItem pack_general_config(const DplDevice::GroupPointer &groupPointer);
    MetaItem pack_focallaw_config(const DplDevice::GroupPointer &groupPointer);

    MetaItem pack_gate_config(const DplDevice::GroupPointer &groupPointer, DplFpga::Group::GateType type);
    MetaItem pack_tcgs_config(const DplDevice::GroupPointer &groupPointer);

    void unpack_group_item_config(int key, const MetaItem &item);
    void unpack_group_gate_config(int key, const MetaItem &item);
    void unpack_group_ut_config(int key, const MetaItem &item);
    void unpack_group_focallaw_config(int key, const MetaItem &item);
    void unpack_group_probe_part_config(int key, const MetaItem &item);
    void unpack_group_scan_config(int key, const MetaItem &item);
    void unpack_group_measurement_config(int key, const MetaItem &item);

};

}

#endif // GROUPCONFIG_H
