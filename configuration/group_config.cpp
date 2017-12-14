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
    m_packer->pack_map(groups.size());

    while(it != groups.end()) {
        const DplDevice::GroupPointer groupPointer = (*it);
        pack_group_child_item_config(groupPointer);
        ++it;
    }
}

bool GroupConfig::unpack(const msgpack::v2::object &obj)
{
    try {

        if(obj.type != msgpack::type::MAP) {
            qDebug() << "[" << __FUNCTION__ << "]" << " object type is not MAP!";
            return false;
        }

        MetaItem groupMap;
        obj.convert(groupMap);

        std::map<int, msgpack::object>::iterator it = groupMap.begin();

        DplDevice::Device *device = DplDevice::Device::instance();
        int groupCount = groupMap.size() - device->group_qty();

        if(groupCount < 0) {
            /* 删除多余组 */
            for(int i = groupCount; i < 0; ++i) {
                if(!device->remove_group(device->group_qty() - 1)) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " remove group id = " << device->group_qty() - 1 << " failed!";
                    return false;
                }
            }
        } if(groupCount > 0) {
            /* 增加组 */
            for(int i = groupCount; i > 0; --i) {
                if(!device->add_group()) {
                    qDebug() << "[" << __FUNCTION__ << "]" << " remove group id = " << device->group_qty() - 1 << " failed!";
                    return false;
                }
            }
        }

        while(it != groupMap.end()) {

            m_groupPointer = device->get_group(it->first);

            if(it->second.type == msgpack::type::MAP) {
                msgpack::object_kv *currentKV = it->second.via.map.ptr;
                for(uint i = 0; i < it->second.via.map.size; ++i) {
                    unpack_group_item_config(currentKV[i].key.as<int>(), currentKV[i].val);
                }
            }
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
    /* key */
    m_packer->pack_int(groupPointer->index());
     /* values */
    m_packer->pack_map((int)Config_Group::GroupItemNum);

    pack_group_general_config(groupPointer);

    pack_group_gate_config(groupPointer);

    pack_group_ut_config(groupPointer);

    pack_group_focallawer_config(groupPointer);

    pack_group_dacs_config(groupPointer);

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

    generalItemMap.insert(MetaItem::value_type((int)Config_Group::General_CurrentBeamIndex,
                                                msgpack::object(groupPointer->current_beam_index(), zone)));
    /* key */
    m_packer->pack((int)Config_Group::General);
    /* value */
    m_packer->pack(generalItemMap);
}

void GroupConfig::pack_group_gate_config(const DplDevice::GroupPointer &groupPointer)
{
    /* key */
    m_packer->pack((int)Config_Group::Gate);

    /* value */
    int gateCount = 3;
    m_packer->pack_map(gateCount);

    pack_gate_config(groupPointer, DplFpga::Group::GATE_A);

    pack_gate_config(groupPointer, DplFpga::Group::GATE_B);

    pack_gate_config(groupPointer, DplFpga::Group::GATE_I);

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

void GroupConfig::pack_group_dacs_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::DACS);
    m_packer->pack(2222);
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

    m_packer->pack((int)Config_Group::TCGS_CurrentPointIndex);
    m_packer->pack(tcgs->current_point_index());

    m_packer->pack((int)Config_Group::TCGS_TcgList);
    m_packer->pack_map(tcgs->count());

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

void GroupConfig::pack_gate_config(const DplDevice::GroupPointer &groupPointer, DplFpga::Group::GateType type)
{
    const DplGate::GatePointer &gatePointer = groupPointer->gate(type);

    m_packer->pack((int)type);
    m_packer->pack_map((int)Config_Group::Gate_ItemNum);

    m_packer->pack((int)Config_Group::Gate_Type);
    m_packer->pack((int)gatePointer->type());

    m_packer->pack((int)Config_Group::Gate_Switch);
    m_packer->pack(gatePointer->is_visible());

    m_packer->pack((int)Config_Group::Gate_Start);
    m_packer->pack(gatePointer->start());

    m_packer->pack((int)Config_Group::Gate_Width);
    m_packer->pack(gatePointer->width());

    m_packer->pack((int)Config_Group::Gate_Height);
    m_packer->pack(gatePointer->height());

    m_packer->pack((int)Config_Group::Gate_Synchro);
    m_packer->pack((int)gatePointer->synchro_mode());

    m_packer->pack((int)Config_Group::Gate_Measure);
    m_packer->pack((int)gatePointer->measure_mode());

    std::vector<int> rgb;
    rgb.push_back(gatePointer->color().red());
    rgb.push_back(gatePointer->color().green());
    rgb.push_back(gatePointer->color().blue());
    rgb.push_back(gatePointer->color().alpha());

    m_packer->pack((int)Config_Group::Gate_Color);
    m_packer->pack(rgb);
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
}

void GroupConfig::pack_focallawer_probe_config(const DplDevice::GroupPointer &groupPointer)
{
    m_packer->pack((int)Config_Group::Probe);

    m_packer->pack_map((int)Config_Group::Probe_ItemNum);

    const DplFocallaw::ProbePointer &probe = groupPointer->focallawer()->probe();

    m_packer->pack((int)Config_Group::Probe_PA);
    m_packer->pack(probe->is_pa());

    m_packer->pack((int)Config_Group::Probe_FileName);

#if 0
    //TODO
    if(probe->is_pa()) {
        DplFocallaw::PaProbePointer paPointer = probe.staticCast<DplFocallaw::PaProbe>();
        m_packer->pack(paPointer->file_name().toStdString());
    } else {
        DplFocallaw::UtProbePointer utPointer = probe.staticCast<DplFocallaw::UtProbe>();
        m_packer->pack(utPointer->file_name().toStdString());
    }
#endif

    std::string fileName = "Probe_FileName";    /* TODO */
    m_packer->pack(fileName);

    qDebug("[%s] pa = %d, filename = %s",
           __FUNCTION__,
           (int)probe->is_pa(),
           fileName.c_str());
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
        case Config_Group::DACS:
        {
            unpack_group_dacs_config(item);
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

        m_groupPointer->set_current_angle(generalItem.at(Config_Group::General_CurrentAngle).as<double>());
        m_groupPointer->set_mode((DplDevice::Group::Mode)generalItem.at(Config_Group::General_Mode).as<int>());
        m_groupPointer->set_ut_unit((DplDevice::Group::UtUnit)generalItem.at(Config_Group::General_UTUnit).as<int>());
        m_groupPointer->set_current_beam(generalItem.at(Config_Group::General_CurrentBeamIndex).as<int>());

    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << "convert group general item catch exception!";
    }
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
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group focallawer item type is not MAP.";
        return;
    }

    MetaItem focallawerItem;
    try {
        item.convert(focallawerItem);

        MetaItem::const_iterator it = focallawerItem.begin();
        while(it != focallawerItem.end()) {

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

void GroupConfig::unpack_group_dacs_config(msgpack::v2::object &item)
{
    if(item.type != msgpack::type::MAP) {
        qDebug() << "["<< __FUNCTION__ << "]" << " group_dacs item type is not MAP.";
        return;
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
        int currentPointIndex = tcgsItem.at((int)Config_Group::TCGS_CurrentPointIndex).as<int>();

        try {

            tcgsItem.at((int)Config_Group::TCGS_TcgList).convert(tcg);

            MetaItem::const_iterator it = tcg.begin();

            while(it != tcg.end()) {
                 if(it->first != tcgs->current_tcg()->index()) {
                     if(!tcgs->set_current_tcg(it->first)) {
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

            tcgs->set_current_tcg(currentIndex);
            tcgs->set_current_point(currentPointIndex);
            tcgs->set_enable(enable);

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

            gatePointer->set_visible(gateItem.at(Config_Group::Gate_Switch).as<bool>());
            gatePointer->set_start(gateItem.at(Config_Group::Gate_Start).as<float>());
            gatePointer->set_width(gateItem.at(Config_Group::Gate_Width).as<float>());
            gatePointer->set_height(gateItem.at(Config_Group::Gate_Height).as<int>());
            gatePointer->set_measure_mode((DplFpga::Group::MeasureMode)gateItem.at(Config_Group::Gate_Measure).as<int>());
            gatePointer->set_synchro_mode((DplFpga::Group::SynchroMode)gateItem.at(Config_Group::Gate_Synchro).as<int>());

            std::vector<int> colorVect;
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
        std::string fileName;
        fileName = probeItem.at(Config_Group::Probe_FileName).as<std::string>();

        /* TODO */
#if 0
        if((DplUt::Transceiver::Mode)probeItem.at(Config_Group::Probe_PA).as<bool>()) {
            DplFocallaw::PaProbePointer paPointer = probePointer.staticCast<DplFocallaw::PaProbe>();
            if(paPointer.isNull()) {
                return;
            }
            paPointer->load(QString::fromStdString(fileName));
        } else {
            DplFocallaw::UtProbePointer utPointer = probePointer.staticCast<DplFocallaw::UtProbe>();
            if(utPointer.isNull()) {
                return;
            }
            utPointer->load(QString::fromStdString(fileName));
        }
#endif
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
//TODO
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
    for(int k = 0; k < arraySize; ++k) {

        if(tcgs->current_point_index() != k) {
            if(!tcgs->set_current_point(k)) {
                qDebug() << "[" << __FUNCTION__ << "]" << " faile continue ";
                continue;
            }
        }

        if(points[k].type == msgpack::type::MAP) {

            MetaItem pointsItem;
            try {
               points[k].convert(pointsItem);

               tcgs->set_position(pointsItem.at((int)Config_Group::Point_Position).as<int>());
               tcgs->set_gain(pointsItem.at((int)Config_Group::Point_Gain).as<float>());
            } catch (...) {
                qDebug() << "[" << __FUNCTION__ << "]" << " convert point list catch exception!";
            }
        }
    }
}

}

