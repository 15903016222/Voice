#include "group_config.h"
#include <focallaw/pa_probe.h>

namespace Config {

std::string g_string("doppler");
msgpack::zone g_zone;

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
    m_packer->pack_int((int)Config::Group);
    /* value */
    m_packer->pack_map(groups.size() + 1);

    while(it != groups.end()) {

        const DplDevice::GroupPointer groupPointer = (*it);
        pack_group_child_item_config(groupPointer);
        ++it;
    }

    pack_group_child_item_config(DplDevice::GroupPointer());
}

bool GroupConfig::unpack(const msgpack::v2::object &obj)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter. type = " << obj.type;

    try {

        if(obj.type != msgpack::type::MAP) {
            qDebug() << "[" << __FUNCTION__ << "]" << " object type is not MAP!";
            return false;
        }

        std::map<int, SubItemMap> groupMap;
        obj.convert(groupMap);

        std::map<int, SubItemMap>::iterator it = groupMap.begin();

        qDebug() << "["<< __FUNCTION__ << "]" << " groupMap size  = " << groupMap.size();

        DplDevice::Device *device = DplDevice::Device::instance();
        int groupCount = groupMap.size() - device->group_qty();

        if(groupCount < 0) {
            /* 删除多余组 */
            for(int i = groupCount; i < 0; ++i) {
                if(!device->remove_group(device->group_qty() - 1)) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " remove group id = " << device->group_qty() - 1 << " failed!";
                    return false;
                } else {
                    qDebug() << "[" << __FUNCTION__ << "]" << " remove group success!";
                }
            }
        } if(groupCount > 0) {
            /* 增加组 */
            for(int i = groupCount; i > 0; --i) {
                if(!device->add_group()) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " remove group id = " << device->group_qty() - 1 << " failed!";
                    return false;
                } else {
                    qDebug() << "[" << __FUNCTION__ << "]" << " add group success!";
                }
            }
        }

        while(it != groupMap.end()) {

            m_groupPointer = device->get_group(it->first);

            qDebug() << "[" << __FUNCTION__ << "]" << " group index  = " << it->first;

            SubItemMap::iterator subIt = it->second.begin();
            while(subIt != it->second.end()) {
                unpack_group_item_config(subIt->first, subIt->second);
                ++subIt;
            }
            qDebug() << "=============end group " << it->first << "==============\n";
            ++it;
        }
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert SubItemMap catch execption!";
        return false;
    }

    return true;
}

void GroupConfig::pack_group_child_item_config(const DplDevice::GroupPointer &groupPointer)
{

#if 1
    if(groupPointer.isNull()) {
        /* key */
        m_packer->pack_int(1);

        SubItemMap childItemMap;

        MetaItem gateMetaItem;
        childItemMap.insert(SubItemMap::value_type((int)Config_Group::Gate, gateMetaItem));

        MetaItem utMetaItem;
        childItemMap.insert(SubItemMap::value_type((int)Config_Group::UT, utMetaItem));

        MetaItem focallawMetaItem;
        childItemMap.insert(SubItemMap::value_type((int)Config_Group::Focallawer, focallawMetaItem));

        /* value */
        m_packer->pack(childItemMap);
        return;
    }
#endif

    /* key */
    m_packer->pack_int(groupPointer->index());

    SubItemMap childItemMap;

//    MetaItem generalMetaItem = pack_group_general_config(groupPointer);
//    childItemMap.insert(SubItemMap::value_type((int)Config_Group::General, generalMetaItem));

//    MetaItem gateMetaItem = pack_group_gate_config(groupPointer);
//    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Gate, gateMetaItem));

    MetaItem utMetaItem = pack_group_ut_config(groupPointer);
    childItemMap.insert(SubItemMap::value_type((int)Config_Group::UT, utMetaItem));


    MetaItem test = pack_group_focallawertest_config(groupPointer);
    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Focallawer, test));

    {
        std::string mystring("1");
        msgpack::zone ttttzone;
        ttttzone.allocate_align(mystring.size());
        msgpack::object myobject(mystring, ttttzone);
        qDebug() << "[" << __FUNCTION__ << "]" << " except type = " << myobject.type;
    }

//    std::string mystring("88888888111111");
//    MetaItem test;
//    msgpack::zone zonetest;
//    zonetest.allocate<std::string>();
//    test.insert(MetaItem::value_type(11, msgpack::object(mystring, zonetest)));
//    qDebug() << "[" << __FUNCTION__ << "]" << " type  = " << test.at(11).type;

//    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 1";

//    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Focallawer, test));

    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 2";

//    MetaItem focallawerMetaItem = pack_group_focallawer_config(groupPointer);
//    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Focallawer, focallawerMetaItem));

//    MetaItem tcgsMetaItem = pack_group_tcgs_config(groupPointer);
//    childItemMap.insert(SubItemMap::value_type((int)Config_Group::TCGS, tcgsMetaItem));

//    MetaItem cursorMetaItem = pack_group_cursor_config(groupPointer);
//    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Cursor, cursorMetaItem));

//    MetaItem scanMetaItem = pack_group_scan_config(groupPointer);
//    childItemMap.insert(SubItemMap::value_type((int)Config_Group::Scan, scanMetaItem));

    /* value */
    m_packer->pack(childItemMap);
    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 3";
}

MetaItem GroupConfig::pack_group_general_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem generalItemMap;
    msgpack::zone zone;

    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_Mode,
                                               msgpack::object((int)groupPointer->mode(), zone)));
    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_UTUnit,
                                               msgpack::object((int)groupPointer->ut_unit(), zone)));
    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_CurrentAngle,
                                                msgpack::object(groupPointer->current_angle(), zone)));
    return generalItemMap;
}

MetaItem GroupConfig::pack_group_gate_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem gateMap;
    msgpack::zone zoneA, zoneB, zoneI;
    MetaItem  gateItemMapA = pack_gate_config(gateItemMapA, zoneA, groupPointer, DplFpga::Group::GATE_A);
    MetaItem  gateItemMapB = pack_gate_config(gateItemMapB, zoneB, groupPointer, DplFpga::Group::GATE_B);
    MetaItem  gateItemMapI = pack_gate_config(gateItemMapI, zoneI, groupPointer, DplFpga::Group::GATE_I);

    msgpack::zone zone;
    gateMap.insert(MetaItem::value_type((int)DplFpga::Group::GATE_A, msgpack::object(gateItemMapA, zone)));
    gateMap.insert(MetaItem::value_type((int)DplFpga::Group::GATE_B, msgpack::object(gateItemMapB, zone)));
    gateMap.insert(MetaItem::value_type((int)DplFpga::Group::GATE_I, msgpack::object(gateItemMapI, zone)));

    return gateMap;
}

MetaItem GroupConfig::pack_group_ut_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem utItemMap;

    MetaItem sampleItemMap      = pack_ut_sample_config(groupPointer);;
    MetaItem transceiverItemMap = pack_ut_transceiver_config(groupPointer);

    msgpack::zone zone;
    utItemMap.insert(MetaItem::value_type((int)Config_Group::UT_Sample,
                                          msgpack::object(sampleItemMap, zone)));
    utItemMap.insert(MetaItem::value_type((int)Config_Group::UT_Transceiver,
                                          msgpack::object(transceiverItemMap, zone)));
    return utItemMap;
}


MetaItem GroupConfig::pack_group_focallawertest_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem utItemMap;

    MetaItem sampleItemMap = pack_focallawer_probetest_config(g_zone, groupPointer);
    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 1";
    MetaItem transceiverItemMap = pack_focallawer_wedgetest_config(groupPointer);
    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 2";

    msgpack::zone zone;
    utItemMap.insert(MetaItem::value_type((int)Config_Group::Probe,
                                          msgpack::object(sampleItemMap, zone)));
    utItemMap.insert(MetaItem::value_type((int)Config_Group::Wedge,
                                          msgpack::object(transceiverItemMap, zone)));
    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 3";
    return utItemMap;
}

MetaItem GroupConfig::pack_focallawer_probetest_config(msgpack::zone &zone2, const DplDevice::GroupPointer &groupPointer)
{
    MetaItem probeItemMap;

    const DplFocallaw::ProbePointer &probe = groupPointer->focallawer()->probe();

    msgpack::zone zone1;
    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_PA,
                                              msgpack::object(probe->is_pa(), zone1)));

    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 1";
    std::string oo = "hello";
    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_FileName,
                                              msgpack::object(oo, zone1)));
    qDebug() << "[" << __FUNCTION__ << "]" << " debug ... 2";
    return probeItemMap;
}

MetaItem GroupConfig::pack_focallawer_wedgetest_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem probeItemMap;
    return probeItemMap;
}


MetaItem GroupConfig::pack_group_focallawer_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  focallawerItemMap;

    msgpack::zone zone2;
    MetaItem probeItemMap    = pack_focallawer_probe_config(zone2, groupPointer);;
    MetaItem wedgeItemMap    = pack_focallawer_wedge_config(groupPointer);
    MetaItem specimenItemMap = pack_focallawer_specimen_config(groupPointer);
    MetaItem focusCnfItemMap = pack_focallawer_focusCnf_config(groupPointer);

    msgpack::zone zone;

    focallawerItemMap.insert(MetaItem::value_type((int)Config_Group::Probe,
                                          msgpack::object(probeItemMap, zone)));
    focallawerItemMap.insert(MetaItem::value_type((int)Config_Group::Wedge,
                                          msgpack::object(wedgeItemMap, zone)));
    focallawerItemMap.insert(MetaItem::value_type((int)Config_Group::Specimen,
                                          msgpack::object(specimenItemMap, zone)));
    focallawerItemMap.insert(MetaItem::value_type((int)Config_Group::FocusCnf,
                                          msgpack::object(focusCnfItemMap, zone)));

    return focallawerItemMap;
}

MetaItem GroupConfig::pack_group_tcgs_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  tcgsItemMap;
    return tcgsItemMap;
}

MetaItem GroupConfig::pack_group_cursor_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  cursorItemMap;
    return cursorItemMap;
}

MetaItem GroupConfig::pack_group_scan_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  scanItemMap;
    return scanItemMap;
}

MetaItem GroupConfig::pack_gate_config(MetaItem &gateItemMap1, msgpack::zone &zone1, const DplDevice::GroupPointer &groupPointer, DplFpga::Group::GateType type)
{
    const DplGate::GatePointer &gatePointer = groupPointer->gate(type);

    MetaItem gateItemMap;
    msgpack::zone zone;
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Type, msgpack::object((int)gatePointer->type(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Start, msgpack::object(gatePointer->start(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Width, msgpack::object(gatePointer->width(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Height, msgpack::object(gatePointer->height(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Synchro, msgpack::object((int)gatePointer->synchro_mode(), zone)));
    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Measure, msgpack::object((int)gatePointer->measure_mode(), zone)));

    std::vector<unsigned char> rgb;
    rgb.push_back((unsigned char)gatePointer->color().red());
    rgb.push_back((unsigned char)gatePointer->color().green());
    rgb.push_back((unsigned char)gatePointer->color().blue());
    rgb.push_back((unsigned char)gatePointer->color().alpha());

    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Color, msgpack::object(rgb, zone)));
     /* TODO：闸门模式 */
//    gateItemMap.insert(MetaItem::value_type((int)Config_Group::Gate_Mode, msgpack::object((int)gatePointer->mode(), zone)));
    return gateItemMap;
}

MetaItem  GroupConfig::pack_tcgs_config(MetaItem &tcgsItemMap1, msgpack::zone &zone1, const DplDevice::GroupPointer &groupPointer)
{
    const DplSizing::TcgsPointer &tcgsPointer = groupPointer->tcgs();
    MetaItem tcgsItemMap;
    msgpack::zone zone;
    tcgsItemMap.insert(MetaItem::value_type((int)Config_Group::TCGS, msgpack::object(tcgsPointer->count(), zone)));
}

MetaItem GroupConfig::pack_ut_sample_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  sampleItemMap;
    const DplUt::SamplePointer &samplePointer = groupPointer->sample();
    msgpack::zone zone;
    sampleItemMap.insert(MetaItem::value_type((int)Config_Group::Sample_Precision,
                                              msgpack::object(samplePointer->precision(), zone)));
    sampleItemMap.insert(MetaItem::value_type((int)Config_Group::Sample_Gain,
                                              msgpack::object(samplePointer->gain(), zone)));
    sampleItemMap.insert(MetaItem::value_type((int)Config_Group::Sample_Start,
                                              msgpack::object(samplePointer->start(), zone)));
    sampleItemMap.insert(MetaItem::value_type((int)Config_Group::Sample_Range,
                                              msgpack::object(samplePointer->range(), zone)));
    sampleItemMap.insert(MetaItem::value_type((int)Config_Group::Sample_PointQty,
                                              msgpack::object(samplePointer->point_qty(), zone)));
    sampleItemMap.insert(MetaItem::value_type((int)Config_Group::Sample_AutoSet,
                                              msgpack::object(samplePointer->is_auto_set_point_qty(), zone)));

    qDebug("precision = %f, gain = %f, start = %f, range = %f, point_qty = %d, is_auto_set_point_qty = %d, ",
           samplePointer->precision(),
           samplePointer->gain(),
           samplePointer->start(),
           samplePointer->range(),
           samplePointer->point_qty(),
           (int)samplePointer->is_auto_set_point_qty());

    return sampleItemMap;
}

MetaItem GroupConfig::pack_ut_transceiver_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem  transceiverItemMap;
    const DplUt::TransceiverPointer &tPointer = groupPointer->transceiver();

    msgpack::zone zone;
    transceiverItemMap.insert(MetaItem::value_type((int)Config_Group::Transceiver_Mode,
                                              msgpack::object((int)tPointer->mode(), zone)));
    transceiverItemMap.insert(MetaItem::value_type((int)Config_Group::Transceiver_PW,
                                              msgpack::object(tPointer->pw(), zone)));
    transceiverItemMap.insert(MetaItem::value_type((int)Config_Group::Transceiver_Filter,
                                              msgpack::object(tPointer->filter(), zone)));
    transceiverItemMap.insert(MetaItem::value_type((int)Config_Group::Transceiver_Rectifier,
                                              msgpack::object((int)tPointer->rectifier(), zone)));
    transceiverItemMap.insert(MetaItem::value_type((int)Config_Group::Transceiver_VideoFilter,
                                              msgpack::object(tPointer->video_filter(), zone)));
    transceiverItemMap.insert(MetaItem::value_type((int)Config_Group::Transceiver_Averaging,
                                              msgpack::object((int)tPointer->averaging(), zone)));

    qDebug("[%s] Mode = %d, PW = %f, Filter = %d, "
           "Rectifier = %d, VideoFilter = %d, Averaging = %d",
           __FUNCTION__,
           tPointer->mode(),
           tPointer->pw(),
           tPointer->filter(),
           tPointer->rectifier(),
           (int)tPointer->video_filter(),
           tPointer->averaging());

    return transceiverItemMap;
}

MetaItem GroupConfig::pack_focallawer_probe_config(msgpack::zone &zone2, const DplDevice::GroupPointer &groupPointer)
{
    MetaItem probeItemMap;

    const DplFocallaw::ProbePointer &probe = groupPointer->focallawer()->probe();

    msgpack::zone zone1;
    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_PA,
                                              msgpack::object(probe->is_pa(), zone1)));
    std::string test("helloworld!");

    msgpack::object object = msgpack::object(test, zone2);
    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_FileName,
                                              object));
//    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_Serial,
//                                              msgpack::object(probe->serial().toStdString(), zone)));
//    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_Model,
//                                              msgpack::object(probe->model().toStdString(), zone)));
//    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_Type,
//                                              msgpack::object((int)probe->type(), zone)));
//    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_Freq,
//                                              msgpack::object(probe->freq(), zone)));
//    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_PulserIndex,
//                                              msgpack::object(probe->pulser_index(), zone)));
//    probeItemMap.insert(MetaItem::value_type((int)Config_Group::Probe_ReceiverInex,
//                                              msgpack::object(probe->receiver_index(), zone)));

//    qDebug("[%s] pa = %d, filename = %s, serial = %s, "
//           "model = %s, type = %d, freq = %f, pulserIndex = %d, rreceiverIndex = %d",
//           __FUNCTION__,
//           (int)probe->is_pa(),
//           "probeFileName",
//           probe->serial().toStdString().c_str(),
//           probe->model().toStdString().c_str(),
//           (int)probe->type(),
//           probe->freq(),
//           probe->pulser_index(),
//           probe->receiver_index());

    return probeItemMap;
}

MetaItem GroupConfig::pack_focallawer_wedge_config(const DplDevice::GroupPointer &groupPointer)
{
//        FileName
//        Serial
//        Model
//        Angle
//        RootAngle
//        Velocity
//        PrimaryOffset
//        SecondaryOffset
//        FirstElementHeight
//        Length
//        Width
//        Height
//        Orientation
//        delay
    MetaItem probeItemMap;

    return probeItemMap;
}

MetaItem GroupConfig::pack_focallawer_specimen_config(const DplDevice::GroupPointer &groupPointer)
{
//    Type
//    WaveType
//    Velocity
    MetaItem probeItemMap;

    return probeItemMap;
}

MetaItem GroupConfig::pack_focallawer_focusCnf_config(const DplDevice::GroupPointer &groupPointer)
{
//        Mode
    MetaItem focusCnfItemMap;

    return focusCnfItemMap;
}

void GroupConfig::unpack_group_item_config(int key, MetaItem &item)
{
    switch (key) {
        case Config_Group::General:
        {
            unpack_group_general_config(item);
            break;
        }
        case Config_Group::Gate:
        {
            unpack_group_gate_config(item);
            break;
        }
        case Config_Group::UT:
        {
            unpack_group_ut_config(item);
            break;
        }
        case Config_Group::Focallawer:
        {
            unpack_group_focallawer_config(item);
            break;
        }
        case Config_Group::TCGS:
        {
            unpack_group_tcgs_config(item);
            break;
        }
        case Config_Group::Cursor:
        {
            unpack_group_cursor_config(item);
            break;
        }
        case Config_Group::Scan:
        {
            unpack_group_scan_config(item);
            break;
        }
        default:
            break;
    }
    qDebug();
}

void GroupConfig::unpack_group_general_config(MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << item.size();

    qDebug("[GroupConfig::unpack_gate_config] gate mode = %d, UTUnit = %d, currentAngle = %f",
           item.at(Config_Group::General_Mode).as<int>(),
           item.at(Config_Group::General_UTUnit).as<int>(),
           item.at(Config_Group::General_CurrentAngle).as<float>());
}

void GroupConfig::unpack_group_gate_config(MetaItem &item)
{
    MetaItem::iterator it = item.begin();
    while(it != item.end()) {
        unpack_gate_config(it->second);
        ++it;
    }
}

void GroupConfig::unpack_group_ut_config(const MetaItem &item)
{

    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << item.size();
    MetaItem::const_iterator it = item.begin();
    while(it != item.end()) {

        switch (it->first) {
        case Config_Group::UT_Sample:
        {
            unpack_sampe_config(it->second);
            break;
        }
        case Config_Group::UT_Transceiver:
        {
            unpack_transceiver_config(it->second);
            break;
        }
        default:
            break;
        }

        ++it;
    }
}

void GroupConfig::unpack_group_focallawer_config(const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << item.size();
    MetaItem::const_iterator it = item.begin();
    while(it != item.end()) {
        qDebug() << " val type = " << it->second.type;
        ++it;
    }
}

void GroupConfig::unpack_group_tcgs_config(const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << item.size();
}

void GroupConfig::unpack_group_scan_config(const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << item.size();
}

void GroupConfig::unpack_group_cursor_config(const MetaItem &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter.";
}

void GroupConfig::unpack_gate_config(msgpack::v2::object &obj)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << " type = " << obj.type;

    if(obj.type == msgpack::type::MAP) {
       MetaItem gateItem;
       try {
            obj.convert(gateItem);

            DplFpga::Group::GateType gateType = (DplFpga::Group::GateType)gateItem.at(Config_Group::Gate_Type).as<int>();
            DplGate::GatePointer gatePointer = m_groupPointer->gate(gateType);
            gatePointer->set_start(gateItem.at(Config_Group::Gate_Start).as<float>());
            gatePointer->set_width(gateItem.at(Config_Group::Gate_Width).as<float>());
            gatePointer->set_height(gateItem.at(Config_Group::Gate_Height).as<int>());
            gatePointer->set_measure_mode((DplFpga::Group::MeasureMode)gateItem.at(Config_Group::Gate_Measure).as<int>());
            gatePointer->set_synchro_mode((DplFpga::Group::SynchroMode)gateItem.at(Config_Group::Gate_Synchro).as<int>());

            std::vector<unsigned char> colorVect;

            try {
                gateItem.at(Config_Group::Gate_Color).convert(colorVect);
                QColor color(colorVect.at(0), colorVect.at(1), colorVect.at(2), colorVect.at(3));
                gatePointer->set_color(color);
            } catch(...) {
                qDebug() << "["<< __FUNCTION__ << "]" << " convert color vector catch exception!" ;
            }

            qDebug("[GroupConfig::unpack_gate_config] gate type = %d, start = %f, width = %f, height = %d, gateMeasure = %d, synchro = %d",
                   gateItem.at(Config_Group::Gate_Type).as<int>(),
                   gateItem.at(Config_Group::Gate_Start).as<float>(),
                   gateItem.at(Config_Group::Gate_Width).as<float>(),
                   gateItem.at(Config_Group::Gate_Height).as<int>(),
                   gateItem.at(Config_Group::Gate_Measure).as<int>(),
                   gateItem.at(Config_Group::Gate_Synchro).as<int>());

            qDebug() << "red = " << colorVect.at(0) << " green = " << colorVect.at(1)
                     << " blue = " << colorVect.at(2) << " alpha = " << colorVect.at(3);

        } catch(...) {
            qDebug() << "["<< __FUNCTION__ << "]" << " convert gateItem catch exception!";
        }
    }
}

void GroupConfig::unpack_tcg_config(const msgpack::v2::object &obj)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << " type = " << obj.type;
}

void GroupConfig::unpack_sampe_config(const msgpack::v2::object &obj)
{
    if(obj.type == msgpack::type::MAP) {
        try {
            MetaItem itemMap;
            obj.convert(itemMap);

            DplUt::SamplePointer sample= m_groupPointer->sample();
//            sample->set_precision();
            sample->set_gain(itemMap.at(Config_Group::Sample_Gain).as<float>());
            sample->set_start(itemMap.at(Config_Group::Sample_Start).as<float>());
            sample->set_range(itemMap.at(Config_Group::Sample_Range).as<float>());
            sample->set_point_qty(itemMap.at(Config_Group::Sample_PointQty).as<int>(),
                                  itemMap.at(Config_Group::Sample_AutoSet).as<bool>());

            qDebug("[%s] Precision = %f, Gain = %f, Start = %f, Range = %d, "
                   "PointQty = %d, AutoSet = %d",
                   __FUNCTION__,
                   itemMap.at(Config_Group::Sample_Precision).as<float>(),
                   itemMap.at(Config_Group::Sample_Gain).as<float>(),
                   itemMap.at(Config_Group::Sample_Start).as<float>(),
                   itemMap.at(Config_Group::Sample_Range).as<float>(),
                   itemMap.at(Config_Group::Sample_PointQty).as<int>(),
                   (int)itemMap.at(Config_Group::Sample_AutoSet).as<bool>());

        } catch (...) {
            qDebug() << "[" << __FUNCTION__ << "]" << " convert sample item catch exception!";
        }
    }
}

void GroupConfig::unpack_transceiver_config(const msgpack::v2::object &obj)
{
    if(obj.type == msgpack::type::MAP) {
        try {
            MetaItem itemMap;
            obj.convert(itemMap);

            DplUt::TransceiverPointer transceiver= m_groupPointer->transceiver();
            transceiver->set_mode((DplUt::Transceiver::Mode)itemMap.at(Config_Group::Transceiver_Mode).as<int>());
            transceiver->set_pw(itemMap.at(Config_Group::Transceiver_PW).as<float>());
            transceiver->set_filter(itemMap.at(Config_Group::Transceiver_Filter).as<int>());
            transceiver->set_rectifier((DplFpga::Group::Rectifier)itemMap.at(Config_Group::Transceiver_Rectifier).as<int>());
            transceiver->set_video_filter(itemMap.at(Config_Group::Transceiver_VideoFilter).as<bool>());
            transceiver->set_averaging((DplFpga::Group::Averaging)itemMap.at(Config_Group::Transceiver_Averaging).as<int>());

            qDebug("[%s] Mode = %d, PW = %f, Filter = %d, "
                   "Rectifier = %d, VideoFilter = %d, Averaging = %d",
                   __FUNCTION__,
                   itemMap.at(Config_Group::Transceiver_Mode).as<int>(),
                   itemMap.at(Config_Group::Transceiver_PW).as<float>(),
                   itemMap.at(Config_Group::Transceiver_Filter).as<int>(),
                   itemMap.at(Config_Group::Transceiver_Rectifier).as<int>(),
                   (int)itemMap.at(Config_Group::Transceiver_VideoFilter).as<bool>(),
                   itemMap.at(Config_Group::Transceiver_Averaging).as<int>());

        } catch (...) {
            qDebug() << "[" << __FUNCTION__ << "]" << " convert transceiver item catch exception!";
        }
    }
}

void GroupConfig::unpack_focallawer_probe_config(const msgpack::v2::object &obj)
{

}

void GroupConfig::unpack_focallawer_wedge_config(const msgpack::v2::object &obj)
{

}

void GroupConfig::unpack_focallawer_specimen_config(const msgpack::v2::object &obj)
{

}

void GroupConfig::unpack_focallawer_focusCnf_config(const msgpack::v2::object &obj)
{

}

}

