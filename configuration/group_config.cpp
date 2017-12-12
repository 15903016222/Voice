#include "group_config.h"
#include <focallaw/pa_probe.h>

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

        MetaItem groupMap;
        obj.convert(groupMap);

        std::map<int, msgpack::object>::iterator it = groupMap.begin();

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

            if(it->second.type == msgpack::type::MAP) {
                msgpack::object_kv *currentKV = it->second.via.map.ptr;
                for(uint i = 0; i < it->second.via.map.size; ++i) {
                    unpack_group_item_config(currentKV[i].key.as<int>(), currentKV[i].val);
                }
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
        /* value */
        m_packer->pack_map(3);

        m_packer->pack((int)Config_Group::Gate);
        m_packer->pack(222);

        m_packer->pack((int)Config_Group::UT);
        m_packer->pack(222);

        m_packer->pack((int)Config_Group::Focallawer);
        m_packer->pack(222);

        return;
    }
#endif

    /* key */
    m_packer->pack_int(groupPointer->index());

     /* values */
    m_packer->pack_map((int)Config_Group::GroupItemNum);

    pack_group_general_config(groupPointer);

    pack_group_gate_config(groupPointer);

    pack_group_ut_config(groupPointer);

    pack_group_focallawer_config(groupPointer);

    pack_group_tcgs_config(groupPointer);

    pack_group_cursor_config(groupPointer);

    pack_group_scan_config(groupPointer);

}

void GroupConfig::pack_group_general_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem generalItemMap;
    msgpack::zone zone;

    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_Mode,
                                               msgpack::object((int)groupPointer->mode(), zone)));
    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_UTUnit,
                                               msgpack::object((int)groupPointer->ut_unit(), zone)));
    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_CurrentAngle,
                                                msgpack::object(groupPointer->current_angle(), zone)));
    /* key */
    m_packer->pack((int)Config_Group::General);
    /* value */
    m_packer->pack(generalItemMap);
}

void GroupConfig::pack_group_gate_config(const DplDevice::GroupPointer &groupPointer)
{
    MetaItem gateMap;

    MetaItem  gateItemMapA = pack_gate_config(groupPointer, DplFpga::Group::GATE_A);
    MetaItem  gateItemMapB = pack_gate_config(groupPointer, DplFpga::Group::GATE_B);
    MetaItem  gateItemMapI = pack_gate_config(groupPointer, DplFpga::Group::GATE_I);

    msgpack::zone zone;
    gateMap.insert(MetaItem::value_type((int)DplFpga::Group::GATE_A, msgpack::object(gateItemMapA, zone)));
    gateMap.insert(MetaItem::value_type((int)DplFpga::Group::GATE_B, msgpack::object(gateItemMapB, zone)));
    gateMap.insert(MetaItem::value_type((int)DplFpga::Group::GATE_I, msgpack::object(gateItemMapI, zone)));

    /* key */
    m_packer->pack((int)Config_Group::Gate);
    /* value */
    m_packer->pack(gateMap);
}

void GroupConfig::pack_group_ut_config(const DplDevice::GroupPointer &groupPointer)
{
    /* key */
    m_packer->pack((int)Config_Group::UT);
    m_packer->pack_map((int)Config_Group::UT_ItemNum);

    pack_ut_sample_config(groupPointer);

    pack_ut_transceiver_config(groupPointer);
}

void GroupConfig::pack_group_focallawer_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::Focallawer);

    m_packer->pack_map((int)Config_Group::Focallawer_ItemNum);

    pack_focallawer_probe_config(groupPointer);

    pack_focallawer_wedge_config(groupPointer);

    pack_focallawer_specimen_config(groupPointer);

    pack_focallawer_focusCnf_config(groupPointer);
}

void GroupConfig::pack_group_tcgs_config(const DplDevice::GroupPointer &groupPointer)
{
    const DplSizing::TcgsPointer &tcgs = groupPointer->tcgs();

    m_packer->pack((int)Config_Group::TCGS);

    m_packer->pack_map((int)Config_Group::TCGS_ItemNum);

    m_packer->pack((int)Config_Group::TCGS_Enable);
    m_packer->pack(tcgs->enable());

    m_packer->pack((int)Config_Group::TCGS_CurrentTcgIndex);
    m_packer->pack(tcgs->current_tcg()->index());

    m_packer->pack((int)Config_Group::TCGS_TcgList);
    m_packer->pack_map(tcgs->count());

    qDebug() << "[" << __FUNCTION__ << "]" << " enable = " << tcgs->enable()
             << " Index = " << tcgs->current_tcg()->index();

    for(int i = 0; i < tcgs->count(); ++i) {
        /* key */
        m_packer->pack(i);
        DplSizing::TcgPointer tcg = tcgs->tcg(i);
        /* value */
        m_packer->pack_array(tcgs->point_count());

        for(int pointCount = 0; pointCount < tcgs->point_count(); ++pointCount) {

            m_packer->pack_map((int)Config_Group::Point_ItemNum);

            m_packer->pack((int)Config_Group::Point_Index);
            m_packer->pack(pointCount);
            m_packer->pack((int)Config_Group::Point_Gain);
            m_packer->pack(tcg->gain(pointCount));
            m_packer->pack((int)Config_Group::Point_Position);
            m_packer->pack(tcg->position(pointCount));

            qDebug("[%s] index = %d, gain = %f, position = %d",
                   __FUNCTION__,
                   pointCount,
                   tcg->gain(pointCount),
                   tcg->position(pointCount));
        }
    }
}

void GroupConfig::pack_group_cursor_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::Cursor);
    const DplMeasure::CursorPointer &cursor = groupPointer->cursor();

    m_packer->pack_map((int)Config_Group::Cursor_ItemNum);

    m_packer->pack((int)Config_Group::Cursor_AmplitudeReference);
    m_packer->pack(cursor->amplitude_reference());

    m_packer->pack((int)Config_Group::Cursor_AmplitudeMeasurement);
    m_packer->pack(cursor->amplitude_measurement());

    m_packer->pack((int)Config_Group::Cursor_UltrasoundReference);
    m_packer->pack(cursor->ultrasound_reference());

    m_packer->pack((int)Config_Group::Cursor_UltrasoundMeasurement);
    m_packer->pack(cursor->ultrasound_measurement());

    m_packer->pack((int)Config_Group::Cursor_ScanReference);
    m_packer->pack(cursor->scan_reference());

    m_packer->pack((int)Config_Group::Cursor_ScanMeasurement);
    m_packer->pack(cursor->scan_measurement());

    m_packer->pack((int)Config_Group::Cursor_IndexReference);
    m_packer->pack(cursor->index_reference());

    m_packer->pack((int)Config_Group::Cursor_IndexMeasurement);
    m_packer->pack(cursor->index_measurement());

    m_packer->pack((int)Config_Group::Cursor_Visible);
    m_packer->pack(cursor->is_visible());

}

void GroupConfig::pack_group_scan_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::Scan);

    const DplDisplay::SscanPointer &scan = groupPointer->s_scan();

    m_packer->pack_map((int)Config_Group::Scan_ItemNum);

    m_packer->pack((int)Config_Group::Scan_StartX);
    m_packer->pack(scan->start_x());

    m_packer->pack((int)Config_Group::Scan_StopX);
    m_packer->pack(scan->stop_x());

    m_packer->pack((int)Config_Group::Scan_StartY);
    m_packer->pack(scan->start_y());

    m_packer->pack((int)Config_Group::Scan_StopY);
    m_packer->pack(scan->stop_y());

    m_packer->pack((int)Config_Group::Scan_Width);
    m_packer->pack(scan->width());

    m_packer->pack((int)Config_Group::Scan_Height);
    m_packer->pack(scan->height());

}

MetaItem GroupConfig::pack_gate_config(const DplDevice::GroupPointer &groupPointer, DplFpga::Group::GateType type)
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

void GroupConfig::pack_ut_sample_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::UT_Sample);

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

    m_packer->pack(sampleItemMap);

    qDebug("precision = %f, gain = %f, start = %f, range = %f, point_qty = %d, is_auto_set_point_qty = %d, ",
           samplePointer->precision(),
           samplePointer->gain(),
           samplePointer->start(),
           samplePointer->range(),
           samplePointer->point_qty(),
           (int)samplePointer->is_auto_set_point_qty());
}

void GroupConfig::pack_ut_transceiver_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::UT_Transceiver);

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

    m_packer->pack(transceiverItemMap);

    qDebug("[%s] Mode = %d, PW = %f, Filter = %d, "
           "Rectifier = %d, VideoFilter = %d, Averaging = %d",
           __FUNCTION__,
           tPointer->mode(),
           tPointer->pw(),
           tPointer->filter(),
           tPointer->rectifier(),
           (int)tPointer->video_filter(),
           tPointer->averaging());
}

void GroupConfig::pack_focallawer_probe_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::Probe);

    m_packer->pack_map((int)Config_Group::Probe_ItemNum);

    const DplFocallaw::ProbePointer &probe = groupPointer->focallawer()->probe();

    m_packer->pack((int)Config_Group::Probe_PA);
    m_packer->pack(probe->is_pa());

    m_packer->pack((int)Config_Group::Probe_FileName);
    std::string fileName = "Probe_FileName";    /* TODO */
    m_packer->pack(fileName);

    m_packer->pack((int)Config_Group::Probe_Serial);
    m_packer->pack(probe->serial().toStdString());

    m_packer->pack((int)Config_Group::Probe_Model);
    m_packer->pack(probe->model().toStdString());

    m_packer->pack((int)Config_Group::Probe_Type);
    m_packer->pack((int)probe->type());

    m_packer->pack((int)Config_Group::Probe_Freq);
    m_packer->pack(probe->freq());

    m_packer->pack((int)Config_Group::Probe_PulserIndex);
    m_packer->pack(probe->pulser_index());

    m_packer->pack((int)Config_Group::Probe_ReceiverInex);
    m_packer->pack(probe->receiver_index());

    qDebug("[%s] pa = %d, filename = %s, serial = %s, "
           "model = %s, type = %d, freq = %f, pulserIndex = %d, rreceiverIndex = %d",
           __FUNCTION__,
           (int)probe->is_pa(),
           fileName.c_str(),
           probe->serial().toStdString().c_str(),
           probe->model().toStdString().c_str(),
           (int)probe->type(),
           probe->freq(),
           probe->pulser_index(),
           probe->receiver_index());
}

void GroupConfig::pack_focallawer_wedge_config(const DplDevice::GroupPointer &groupPointer)
{
    const DplFocallaw::WedgePointer &wedgePointer = groupPointer->focallawer()->wedge();

    m_packer->pack((int)Config_Group::Wedge);
    m_packer->pack_map((int)Config_Group::Wedge_ItemNum);

    m_packer->pack((int)Config_Group::Wedge_FileName);
    std::string fileName = "wedgeFile";     /* TODO */
    m_packer->pack(fileName);

    m_packer->pack((int)Config_Group::Wedge_Serial);
    m_packer->pack(wedgePointer->serial().toStdString());

    m_packer->pack((int)Config_Group::Wedge_Model);
    m_packer->pack(wedgePointer->model().toStdString());

    m_packer->pack((int)Config_Group::Wedge_Angle);
    m_packer->pack(wedgePointer->angle());

    m_packer->pack((int)Config_Group::Wedge_RootAngle);
    m_packer->pack(wedgePointer->roof_angle());

    m_packer->pack((int)Config_Group::Wedge_Velocity);
    m_packer->pack(wedgePointer->velocity());

    m_packer->pack((int)Config_Group::Wedge_PrimaryOffset);
    m_packer->pack(wedgePointer->primary_offset());

    m_packer->pack((int)Config_Group::Wedge_SecondaryOffset);
    m_packer->pack(wedgePointer->secondary_offset());

    m_packer->pack((int)Config_Group::Wedge_FirstElementHeight);
    m_packer->pack(wedgePointer->first_element_height());

    m_packer->pack((int)Config_Group::Wedge_Length);
    m_packer->pack(wedgePointer->length());

    m_packer->pack((int)Config_Group::Wedge_Width);
    m_packer->pack(wedgePointer->width());

    m_packer->pack((int)Config_Group::Wedge_Height);
    m_packer->pack(wedgePointer->height());

    m_packer->pack((int)Config_Group::Wedge_Orientation);
    m_packer->pack((int)wedgePointer->orientation());

    m_packer->pack((int)Config_Group::Wedge_delay);
    m_packer->pack(wedgePointer->delay());
}

void GroupConfig::pack_focallawer_specimen_config(const DplDevice::GroupPointer &groupPointer)
{
    const DplFocallaw::SpecimenPointer &specimenPointer = groupPointer->focallawer()->specimen();

    m_packer->pack((int)Config_Group::Specimen);
    m_packer->pack_map((int)Config_Group::Specimen_ItemNum);

    m_packer->pack((int)Config_Group::Specimen_Type);
    m_packer->pack((int)specimenPointer->type());

    m_packer->pack((int)Config_Group::Specimen_WaveType);
    m_packer->pack((int)specimenPointer->wave_type());

    m_packer->pack((int)Config_Group::Specimen_Velocity);
    m_packer->pack(specimenPointer->velocity());

}

void GroupConfig::pack_focallawer_focusCnf_config(const DplDevice::GroupPointer &groupPointer)
{
    const DplFocallaw::FocusCnfPointer &pointer = groupPointer->focallawer()->focus_configure();

    m_packer->pack((int)Config_Group::FocusCnf);
    m_packer->pack_map((int)Config_Group::FocusCnf_ItemNum);
    m_packer->pack((int)Config_Group::FocusCnf_Mode);
    m_packer->pack((int)pointer->mode());
}

void GroupConfig::pack_tcg_config(const DplSizing::TcgsPointer &tcgs, int index)
{
//    DplSizing::TcgPointer tcg = tcgs->tcg(index);
//    tcgs->set_current_tcg(index);
//    tcg->index()
//    tcg->gain() ;

//    m_packer->pack_map((int)Config_Group::TCGS_ItemNum);

//    m_packer->pack((int)Config_Group::TCGS_Enable);
//    m_packer->pack(tcg->gain());
//    m_packer->pack(tcg->position(index));
}

void GroupConfig::unpack_group_item_config(int key, msgpack::object &item)
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

void GroupConfig::unpack_group_general_config(msgpack::object &item)
{
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group general item type is not MAP.";
        return;
    }

    MetaItem generalItem;
    try {
        item.convert(generalItem);
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << "convert group general item catch exception!";
    }

    qDebug("[GroupConfig::unpack_gate_config] gate mode = %d, UTUnit = %d, currentAngle = %f",
           generalItem.at(Config_Group::General_Mode).as<int>(),
           generalItem.at(Config_Group::General_UTUnit).as<int>(),
           generalItem.at(Config_Group::General_CurrentAngle).as<float>());
}

void GroupConfig::unpack_group_gate_config(msgpack::object &item)
{
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group gate item type is not MAP.";
        return;
    }

    MetaItem gateItem;
    try {
        item.convert(gateItem);

        MetaItem::iterator it = gateItem.begin();
        while(it != gateItem.end()) {
            unpack_gate_config(it->second);
            ++it;
        }
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << "convert group gate item catch exception!";
    }
}

void GroupConfig::unpack_group_ut_config(msgpack::object &item)
{
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group ut item type is not MAP.";
        return;
    }

    MetaItem utItem;
    try {
        item.convert(utItem);

        MetaItem::const_iterator it = utItem.begin();
        while(it != utItem.end()) {

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

    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << "convert group ut item catch exception!";
    }
}

void GroupConfig::unpack_group_focallawer_config(msgpack::object &item)
{
    qDebug() << "["<< __FUNCTION__ << "]" << " enter." << item.type;

    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group focallawer item type is not MAP.";
        return;
    }

    MetaItem focallawerItem;
    try {
        item.convert(focallawerItem);

        MetaItem::const_iterator it = focallawerItem.begin();
        while(it != focallawerItem.end()) {
            qDebug() << " val type = " << it->second.type;

            switch (it->first) {
            case Config_Group::Probe:
            {
                unpack_focallawer_probe_config(it->second);
                break;
            }
            case Config_Group::Wedge:
            {
                unpack_focallawer_wedge_config(it->second);
                break;
            }
            case Config_Group::Specimen:
            {
                unpack_focallawer_specimen_config(it->second);
                break;
            }
            case Config_Group::FocusCnf:
            {
                unpack_focallawer_focusCnf_config(it->second);
                break;
            }
            default:
                break;
            }

            ++it;
        }
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << "convert group focallawer item catch exception!";
    }
}

void GroupConfig::unpack_group_tcgs_config(msgpack::object &item)
{
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group_tcgs item type is not MAP.";
        return;
    }

    MetaItem tcgsItem;
    MetaItem tcg;

    try {
        item.convert(tcgsItem);
        DplSizing::TcgsPointer tcgs = m_groupPointer->tcgs();
        bool enable = tcgsItem.at((int)Config_Group::TCGS_Enable).as<bool>();
        int currentIndex = tcgsItem.at((int)Config_Group::TCGS_CurrentTcgIndex).as<int>();

        try {

            tcgsItem.at((int)Config_Group::TCGS_TcgList).convert(tcg);

            MetaItem::const_iterator it = tcg.begin();

            while(it != tcg.end()) {

                qDebug() << "["<< __FUNCTION__ << "]" << " index = " << it->first;

                 if(it->first != tcgs->current_tcg()->index()) {
                     if(!tcgs->set_current_tcg(it->first)) {
                         qDebug() << "["<< __FUNCTION__ << "]" << " continue = ";

                         ++it;
                         continue;
                     }
                 }

                 if(it->second.type == msgpack::type::ARRAY) {

                     int arraySize = it->second.via.array.size;
                     msgpack::object *arrayItem = it->second.via.array.ptr;
                     int pointCount = arraySize - tcgs->point_count();
                     if(pointCount > 0) {
                         /* add point */
                        while(pointCount > 0) {
                            tcgs->add_point();
                            --pointCount;
                        }
                     } else {
                         /* delete point */
                         while(pointCount < 0) {
                             tcgs->delete_point();
                             ++pointCount;
                         }
                     }
                     set_tcg_points(tcgs, arrayItem, arraySize);
                 }
                ++it;
            }

        } catch(...) {
            qDebug() << "[" << __FUNCTION__ << "]" << " convert tcg list catch exception!";
        }
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert tcgs item catch exception!";
    }
}

void GroupConfig::unpack_group_scan_config(msgpack::object &item)
{
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group_scan item type is not MAP.";
        return;
    }

    qDebug() << "["<< __FUNCTION__ << "]" << " object val type = " << item.type;

    MetaItem scanItem;

    try {
        item.convert(scanItem);
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert scan item catch exception!";
    }
}

void GroupConfig::unpack_group_cursor_config(msgpack::object &item)
{
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group_cursor item type is not MAP.";
        return;
    }

    MetaItem cursorItem;

    try {
        item.convert(cursorItem);
        DplMeasure::CursorPointer cursor = m_groupPointer->cursor();

        cursor->set_visible(cursorItem.at(Config_Group::Cursor_Visible).as<bool>());
        cursor->set_amplitude_reference(cursorItem.at(Config_Group::Cursor_AmplitudeReference).as<double>());
        cursor->set_amplitude_measurement(cursorItem.at(Config_Group::Cursor_AmplitudeMeasurement).as<double>());
        cursor->set_ultrasound_reference(cursorItem.at(Config_Group::Cursor_UltrasoundReference).as<double>());
        cursor->set_ultrasound_measurement(cursorItem.at(Config_Group::Cursor_UltrasoundMeasurement).as<double>());
        cursor->set_scan_reference(cursorItem.at(Config_Group::Cursor_ScanReference).as<double>());
        cursor->set_scan_measurement(cursorItem.at(Config_Group::Cursor_ScanMeasurement).as<double>());
        cursor->set_index_reference(cursorItem.at(Config_Group::Cursor_IndexReference).as<double>());
        cursor->set_index_measurement(cursorItem.at(Config_Group::Cursor_IndexMeasurement).as<double>());

    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert cursor item catch exception!";
    }
}

void GroupConfig::unpack_gate_config(msgpack::v2::object &obj)
{
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
            /* TODO */
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
    if(obj.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " focallawer_probe item type is not MAP.";
        return;
    }

    MetaItem probeItem;

    try {
        obj.convert(probeItem);

        DplFocallaw::ProbePointer probePointer = m_groupPointer->focallawer()->probe();
//TODO
//        probePointer->set_pa((DplUt::Transceiver::Mode)probeItem.at(Config_Group::Probe_PA).as<bool>());
//        probePointer->set_file_name(probeItem.at(Config_Group::Probe_FileName).as<std::string>());
        probePointer->set_serial(QString::fromStdString(probeItem.at(Config_Group::Probe_Serial).as<std::string>()));
        probePointer->set_model(QString::fromStdString(probeItem.at(Config_Group::Probe_Model).as<std::string>()));
        probePointer->set_type((DplFocallaw::PaProbe::Type)probeItem.at(Config_Group::Probe_Type).as<int>());
        probePointer->set_freq(probeItem.at(Config_Group::Probe_Freq).as<double>());
        probePointer->set_pulser_index(probeItem.at(Config_Group::Probe_PulserIndex).as<uint>());
        probePointer->set_receiver_index(probeItem.at(Config_Group::Probe_ReceiverInex).as<uint>());

        qDebug("[%s] PA = %d, fileName = %s, Serial = %s, "
               "Model = %s, Type = %d, Freq = %f, "
               "PulserIndex = %d, ReceiverInex = %d",
               __FUNCTION__,
               (int)probeItem.at(Config_Group::Probe_PA).as<bool>(),
               probeItem.at(Config_Group::Probe_FileName).as<std::string>().c_str(),
               probeItem.at(Config_Group::Probe_Serial).as<std::string>().c_str(),
               probeItem.at(Config_Group::Probe_Model).as<std::string>().c_str(),
               probeItem.at(Config_Group::Probe_Type).as<int>(),
               probeItem.at(Config_Group::Probe_Freq).as<double>(),
               probeItem.at(Config_Group::Probe_PulserIndex).as<uint>(),
               probeItem.at(Config_Group::Probe_ReceiverInex).as<uint>());

    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert probe item catch exception!";
    }
}

void GroupConfig::unpack_focallawer_wedge_config(const msgpack::v2::object &obj)
{
    if(obj.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " focallawer_wedge item type is not MAP.";
        return;
    }

    MetaItem wedgeItem;

    try {
        obj.convert(wedgeItem);

        DplFocallaw::WedgePointer wedgePointer = m_groupPointer->focallawer()->wedge();
//TODO
//        std::string fileName = wedgeItem.at(Config_Group::Wedge_FileName).as<std::string>();
//        wedgePointer->set_file_name(QString::fromStdString(fileName));

        std::string serial = wedgeItem.at(Config_Group::Wedge_Serial).as<std::string>();
        wedgePointer->set_serial(QString::fromStdString(serial));

        std::string model = wedgeItem.at(Config_Group::Wedge_Model).as<std::string>();
        wedgePointer->set_model(QString::fromStdString(model));

        wedgePointer->set_angle(wedgeItem.at(Config_Group::Wedge_Angle).as<float>());
        wedgePointer->set_root_angle(wedgeItem.at(Config_Group::Wedge_RootAngle).as<float>());
        wedgePointer->set_velocity(wedgeItem.at(Config_Group::Wedge_Velocity).as<quint32>());
        wedgePointer->set_primary_offset(wedgeItem.at(Config_Group::Wedge_PrimaryOffset).as<float>());
        wedgePointer->set_secondary_offset(wedgeItem.at(Config_Group::Wedge_SecondaryOffset).as<float>());
        wedgePointer->set_first_element_height(wedgeItem.at(Config_Group::Wedge_FirstElementHeight).as<float>());
        wedgePointer->set_length(wedgeItem.at(Config_Group::Wedge_Length).as<float>());
        wedgePointer->set_width(wedgeItem.at(Config_Group::Wedge_Width).as<float>());
        wedgePointer->set_height(wedgeItem.at(Config_Group::Wedge_Height).as<float>());
        wedgePointer->set_orientation((DplFocallaw::Wedge::Orientation)wedgeItem.at(Config_Group::Wedge_Orientation).as<int>());
        wedgePointer->set_delay(wedgeItem.at(Config_Group::Wedge_delay).as<int>());

    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert wedge item catch exception!";
    }

}

void GroupConfig::unpack_focallawer_specimen_config(const msgpack::v2::object &obj)
{
    if(obj.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " focallawer_specimen item type is not MAP.";
        return;
    }

    MetaItem specimenItem;

    try {
        obj.convert(specimenItem);

        DplFocallaw::SpecimenPointer specimenPointer = m_groupPointer->focallawer()->specimen();

//        specimenPointer->set_type(specimenItem.at(Config_Group::Specimen_Velocity).as<int>());
        specimenPointer->set_wave_type((DplFocallaw::Specimen::WaveType)specimenItem.at(Config_Group::Specimen_Type).as<int>());
        specimenPointer->set_velocity(specimenItem.at(Config_Group::Specimen_Velocity).as<uint>());

    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert specimen item catch exception!";
    }

}

void GroupConfig::unpack_focallawer_focusCnf_config(const msgpack::v2::object &obj)
{
    if(obj.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " focallawer_focusCnf item type is not MAP.";
        return;
    }

    MetaItem focusCnfItem;

    try {
        obj.convert(focusCnfItem);

        DplFocallaw::FocusCnfPointer focusCnfPointer = m_groupPointer->focallawer()->focus_configure();
        //focusCnfPointer->set_mode((DplFocallaw::FocusCnf::Mode) focusCnfItem.at(Config_Group::FocusCnf_Mode).as<int>());
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert focusCnf item catch exception!";
    }
}

void GroupConfig::set_tcg_points(DplSizing::TcgsPointer &tcgs, msgpack::object *points, int arraySize)
{
    qDebug() << "[" << __FUNCTION__ << "]" << " array size  = " << arraySize;

    for(int k = 0; k < arraySize; ++k) {

        if(tcgs->current_point_index() != k) {
            if(!tcgs->set_current_point(k)) {
                qDebug() << "[" << __FUNCTION__ << "]" << " faile continue ";
                continue;
            }
        }

        qDebug() << "[" << __FUNCTION__ << "]" << " type = " << points[k].type ;

        if(points[k].type == msgpack::type::MAP) {

            MetaItem pointsItem;
            try {

               points[k].convert(pointsItem);

               tcgs->set_position(pointsItem.at((int)Config_Group::Point_Position).as<int>());
               tcgs->set_gain(pointsItem.at((int)Config_Group::Point_Gain).as<float>());

               qDebug("[%s] index = %d, gain = %f, position = %d",
                      __FUNCTION__,
                      pointsItem.at((int)Config_Group::Point_Index).as<int>(),
                      pointsItem.at((int)Config_Group::Point_Gain).as<float>(),
                      pointsItem.at((int)Config_Group::Point_Position).as<int>());

            } catch (...) {
                qDebug() << "[" << __FUNCTION__ << "]" << " convert point list catch exception!";
            }
        }
    }
}

}

