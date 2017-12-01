#include "preference_config.h"

namespace Config {

PreferenceConfig::PreferenceConfig(msgpack::packer<msgpack::sbuffer> *packer)
    : BaseItemConfig(packer)
{

}

void PreferenceConfig::pack()
{
    /* key */
    m_packer->pack_int((int) Config::Preference);
    /* value */
    MetaItem itemMap;
    msgpack::zone zone;
    itemMap.insert(MetaItem::value_type((int)Config_Preference::Bright, msgpack::object(100, zone)));
    itemMap.insert(MetaItem::value_type((int)Config_Preference::Opacity, msgpack::object(80, zone)));
    itemMap.insert(MetaItem::value_type((int)Config_Preference::Language, msgpack::object(3, zone)));
    itemMap.insert(MetaItem::value_type((int)Config_Preference::StartingPage, msgpack::object(false, zone)));
    itemMap.insert(MetaItem::value_type((int)Config_Preference::GateMode, msgpack::object(false, zone)));

    m_packer->pack(itemMap);
}

void PreferenceConfig::unpack(const msgpack::v2::object &obj)
{
    qDebug() << "[" << __FUNCTION__ << "]" << " enter.";

    try {
        if(obj.type != msgpack::type::MAP) {
            qDebug() << "[" << __FUNCTION__ << "]" << " object type is not MAP!";
            return;
        }

        MetaItem itemMap;
        obj.convert(itemMap);
        MetaItem::const_iterator it = itemMap.begin();
        while(it != itemMap.end())
        {
            switch (it->first) {
            case Config_Preference::Bright:
            {
                qDebug() << "[" << __FUNCTION__ << "]" << " Bright = " << it->second.as<int>();
                break;
            }
            case Config_Preference::Opacity:
            {
                qDebug() << "[" << __FUNCTION__ << "]" << " Opacity = " << it->second.as<int>();
                break;
            }
            case Config_Preference::Language:
            {
                qDebug() << "[" << __FUNCTION__ << "]" << " Language = " << it->second.as<int>();
                break;
            }
            case Config_Preference::StartingPage:
            {
                qDebug() << "[" << __FUNCTION__ << "]" << " StartingPage = " << it->second.as<bool>();
                break;
            }
            case Config_Preference::GateMode:
            {
                qDebug() << "[" << __FUNCTION__ << "]" << " GateMode = " << it->second.as<bool>();
                break;
            }
            default:
                break;
            }

            ++it;
        }
    } catch(...) {
        qDebug() << "[" << __FUNCTION__ << "]" << " convert MetaItem catch execption!";
    }
}

}

