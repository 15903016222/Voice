#include "group_config.h"

namespace Config {

GroupConfig::GroupConfig(msgpack::packer<msgpack::sbuffer> *packer)
    : BaseItemConfig(packer)
{

}

void GroupConfig::pack()
{
    DplDevice::Device *device = DplDevice::Device::instance();

    const QVector<DplDevice::GroupPointer> &groups = device->groups();
    QVector<DplDevice::GroupPointer>::const_iterator it = groups.begin();
    /* key */
    m_packer->pack_int((int) Config::Group);
    /* value */
    m_packer->pack_map(groups.size());

    while(it != groups.end()) {

        const DplDevice::GroupPointer groupPointer = (*it);

        /* key */
        m_packer->pack_int(groupPointer->index());

        pack_group_child_item_config(groupPointer);

        ++it;
    }
}

void GroupConfig::unpack(const msgpack::v2::object &obj)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << obj.type;

    try {
        /* 由于打包时，传进多个map类型的数据，故当前valueObject.via.map.ptr->val才是
         * 是Group里面的item
         */
        if(obj.type != msgpack::type::MAP) {
            qDebug() << "[" << __FUNCTION__ << "]" << " object type is not MAP!";
            return;
        }

        msgpack::object groupMetaItemObj = obj.via.map.ptr->val;
        SubItemMap trueItemMap;
        groupMetaItemObj.convert(trueItemMap);

        qDebug() << "["<< __FUNCTION__ << "]" << " trueItemMap = " << trueItemMap.size();
        SubItemMap::const_iterator it = trueItemMap.begin();
        while(it != trueItemMap.end()) {
            unpack_group_item_config(it->first, it->second);
            ++it;
        }
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert SubItemMap catch execption!";
    }
}

void GroupConfig::pack_group_child_item_config(const DplDevice::GroupPointer &groupPointer)
{
    SubItemMap childItemMap;

    MetaItem metaItem = pack_gate_curves_config(groupPointer);
    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Gate_Curves, metaItem));

    metaItem = pack_ut_config(groupPointer);
    childItemMap.insert(SubItemMap::value_type((int)Config_Group::UT, metaItem));

    metaItem = pack_focallaw_config(groupPointer);
    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Focallaw, metaItem));

    m_packer->pack(childItemMap);
}


MetaItem GroupConfig::pack_gate_curves_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  gateCurvesConfig;

    MetaItem  gateItemMapA = pack_gate_config(groupPointer, DplFpga::Group::GATE_A);
    MetaItem  gateItemMapB = pack_gate_config(groupPointer, DplFpga::Group::GATE_B);
    MetaItem  gateItemMapI = pack_gate_config(groupPointer, DplFpga::Group::GATE_I);
    MetaItem  tcgsItemMap  = pack_tcgs_config(groupPointer);

    msgpack::zone itemZone;
    gateCurvesConfig.insert(MetaItem::value_type((int)Config_Group::Gate, msgpack::object(gateItemMapA, itemZone)));
    gateCurvesConfig.insert(MetaItem::value_type((int)Config_Group::Gate, msgpack::object(gateItemMapB, itemZone)));
    gateCurvesConfig.insert(MetaItem::value_type((int)Config_Group::Gate, msgpack::object(gateItemMapI, itemZone)));
    gateCurvesConfig.insert(MetaItem::value_type((int)Config_Group::TCG, msgpack::object(tcgsItemMap, itemZone)));

    return gateCurvesConfig;
}

MetaItem GroupConfig::pack_ut_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  utItemMap;

    MetaItem  generalConfig =  pack_general_config(groupPointer);

    msgpack::zone itemZone;
    utItemMap.insert(MetaItem::value_type((int)Config_Group::UT, msgpack::object(generalConfig, itemZone)));

    return utItemMap;
}


MetaItem GroupConfig::pack_general_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem generalItemMap;
    msgpack::zone zone;
    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_UTUnit, msgpack::object((int)groupPointer->ut_unit())));

    return generalItemMap;
}

MetaItem GroupConfig::pack_focallaw_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  focallawItemMap;
    return focallawItemMap;
}



MetaItem GroupConfig::pack_gate_config(const DplDevice::GroupPointer &groupPointer, DplFpga::Group::GateType type)
{
    const DplGate::GatePointer &gatePointer = groupPointer->gate(type);

    MetaItem gateItemMap;
    msgpack::zone zone;

    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Type, msgpack::object((int)gatePointer->type(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Start, msgpack::object((int)gatePointer->start(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Width, msgpack::object((int)gatePointer->width(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Height, msgpack::object((int)gatePointer->height(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Synchro, msgpack::object((int)gatePointer->synchro_mode(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Measure, msgpack::object((int)gatePointer->measure_mode(), zone)));

    std::vector<unsigned char> rgb;
    rgb.push_back((unsigned char)gatePointer->color().red());
    rgb.push_back((unsigned char)gatePointer->color().green());
    rgb.push_back((unsigned char)gatePointer->color().blue());
    rgb.push_back((unsigned char)gatePointer->color().alpha());

    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Color, msgpack::object(rgb, zone)));
     /* TODO：闸门模式 */
    //gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Mode, msgpack::object((int)gatePointer->mode(), zone)));

    return gateItemMap;
}

MetaItem GroupConfig::pack_tcgs_config(const DplDevice::GroupPointer &groupPointer)
{
    const DplSizing::TcgsPointer &tcgsPointer = groupPointer->tcgs();

    MetaItem tcgsItemMap;
    msgpack::zone zone;

    tcgsItemMap.insert(MetaItem::value_type((int)Config_Group::TCG_Index, msgpack::object(tcgsPointer->count(), zone)));

    return tcgsItemMap;
}

void GroupConfig::unpack_group_item_config(int key, const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";

    switch (key) {
        case Config_Group::Gate_Curves:
        {
            unpack_group_gate_config(key, item);
            break;
        }
        case Config_Group::UT:
        {
            unpack_group_ut_config(key, item);
            break;
        }
        case Config_Group::Focallaw:
        {
            unpack_group_focallaw_config(key, item);
            break;
        }
        case Config_Group::Probe_Part:
        {
            unpack_group_probe_part_config(key, item);
            break;
        }
        case Config_Group::Scan:
        {
            unpack_group_scan_config(key, item);
            break;
        }
        case Config_Group::Measurement:
        {
            unpack_group_measurement_config(key, item);
            break;
        }
        default:
            break;
    }
}

void GroupConfig::unpack_group_gate_config(int key, const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";
}

void GroupConfig::unpack_group_ut_config(int key, const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";
}

void GroupConfig::unpack_group_focallaw_config(int key, const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";
}

void GroupConfig::unpack_group_probe_part_config(int key, const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";
}

void GroupConfig::unpack_group_scan_config(int key, const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";
}

void GroupConfig::unpack_group_measurement_config(int key, const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";
}


}

