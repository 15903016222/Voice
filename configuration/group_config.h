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
    virtual bool unpack(const msgpack::v2::object &obj);

private:

    void pack_group_child_item_config(const DplDevice::GroupPointer &groupPointer);

    void pack_group_general_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_gate_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_ut_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_focallawer_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_tcgs_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_cursor_config(const DplDevice::GroupPointer &groupPointer);
    void pack_group_scan_config(const DplDevice::GroupPointer &groupPointer);

    MetaItem pack_gate_config(const DplDevice::GroupPointer &groupPointer, DplFpga::Group::GateType type);

    void pack_ut_sample_config(const DplDevice::GroupPointer &groupPointer);
    void pack_ut_transceiver_config(const DplDevice::GroupPointer &groupPointer);

    void pack_focallawer_probe_config(const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_wedge_config(const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_specimen_config(const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_focusCnf_config(const DplDevice::GroupPointer &groupPointer);


    void pack_tcg_config(const DplSizing::TcgsPointer &tcgs, int index);

    void unpack_group_item_config(int key, msgpack::object &item);
    void unpack_group_general_config(msgpack::object &item);
    void unpack_group_gate_config(msgpack::object &item);
    void unpack_group_ut_config(msgpack::object &item);
    void unpack_group_focallawer_config(msgpack::object&item);
    void unpack_group_tcgs_config(msgpack::object &item);
    void unpack_group_scan_config(msgpack::object &item);
    void unpack_group_cursor_config(msgpack::object&item);

    void unpack_gate_config(msgpack::object &obj);
    void unpack_tcg_config(const msgpack::object &obj);
    void unpack_sampe_config(const msgpack::object &obj);
    void unpack_transceiver_config(const msgpack::object &obj);

    void unpack_focallawer_probe_config(const msgpack::object &obj);
    void unpack_focallawer_wedge_config(const msgpack::object &obj);
    void unpack_focallawer_specimen_config(const msgpack::object &obj);
    void unpack_focallawer_focusCnf_config(const msgpack::object &obj);

    void pack_group_focallawertest_config(const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_probetest_config(msgpack::zone &zone2, const DplDevice::GroupPointer &groupPointer);
    void pack_focallawer_wedgetest_config(const DplDevice::GroupPointer &groupPointer);

    void set_tcg_points(DplSizing::TcgsPointer &tcgs, msgpack::object *points, int arraySize);

    DplDevice::GroupPointer m_groupPointer;
};

}

#endif // GROUPCONFIG_H
