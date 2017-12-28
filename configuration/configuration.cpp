#include "configuration.h"

#include <QString>
#include <QFile>
#include <QDebug>

#include "preference_config.h"
#include "group_config.h"

#include <device/device.h>
#include <device/group.h>

namespace Config {

class ConfigurationPrivate {

public:
    ConfigurationPrivate(){}

    QFile                       m_configFile;
    UnpackerMap                 m_unpackerMap;
};

Configuration::Configuration()
    : d(new Config::ConfigurationPrivate)
{
    d->m_unpackerMap.insert(UnpackerMap::value_type((int)Config::Group, new GroupConfig(NULL)));
    d->m_unpackerMap.insert(UnpackerMap::value_type((int)Config::Preference, new PreferenceConfig(NULL)));
}

Configuration::~Configuration()
{
    if(d->m_configFile.isOpen()) {
        d->m_configFile.flush();
        d->m_configFile.close();
    }

    UnpackerMap::iterator it = d->m_unpackerMap.begin();
    while(it != d->m_unpackerMap.end()) {
        if(it->second) {
            BaseItemConfig *current = static_cast<BaseItemConfig*> (it->second);
            if(current) {
                delete it->second;
            }
        }
        ++it;
    }
    d->m_unpackerMap.clear();

    delete d;
}

Configuration *Configuration::instance()
{
    static Configuration *configuration = new Configuration;

    return configuration;
}


bool Configuration::load_config(const QString &configFilePath)
{
    if(configFilePath.isEmpty() || (!QFile::exists(configFilePath))) {
        qDebug() << "[" << __FUNCTION__ << "]" << " config file empty / not exist.";
        return false;
    }

    if(d->m_configFile.isOpen()) {
        d->m_configFile.close();
    }

    d->m_configFile.setFileName(configFilePath);

    if(QFile::exists(configFilePath)) {
        /* 读取配置文件 */
        if(!d->m_configFile.open(QIODevice::ReadOnly)) {
            qDebug() << "[" << __FUNCTION__ << "]" << " open config file failed!";
            return false;
        }

        QDataStream dataStream(&d->m_configFile);

        msgpack::unpacker   unpacker;
        unpacker.reserve_buffer(d->m_configFile.size());
        dataStream.readRawData(unpacker.buffer(), d->m_configFile.size());
        unpacker.buffer_consumed(d->m_configFile.size());

        msgpack::object_handle result;

        while(unpacker.next(result)) {
            msgpack::object object(result.get());
            deal_object(object);
        }
        d->m_configFile.close();
        return true;
    }

    qDebug() << "[" << __FUNCTION__ << "]" << "config file : \"" << configFilePath << "\" not exist!";
    return false;
}

bool Configuration::save_config(const QString &configFilePath)
{
    if(configFilePath.isEmpty()) {
        qDebug() << "[" << __FUNCTION__ << "]" << " config file empty.";
        return false;
    }

    if(d->m_configFile.isOpen()) {
        d->m_configFile.close();
    }

    d->m_configFile.setFileName(configFilePath);
    if(!d->m_configFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "[" << __FUNCTION__ << "]" << " open config file failed!";
        return false;
    }

    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> packer(buffer);

    GroupConfig      groupConfig(&packer);
    PreferenceConfig preConfig(&packer);

    /* 修改此变量，增加map大小 */
    int mapCount = 2;
    packer.pack_map(mapCount);

    groupConfig.pack();
    preConfig.pack();

    QDataStream dataStream(&d->m_configFile);
    dataStream.writeRawData(buffer.data(), buffer.size());

    d->m_configFile.flush();
    d->m_configFile.close();

    return true;
}

void Configuration::deal_object(const msgpack::v2::object &object)
{
    if(object.is_nil()) {
        return;
    }

    if(object.type == msgpack::type::MAP) {

        msgpack::object_kv *firstItem = object.via.map.ptr;
        msgpack::object keyObject;
        msgpack::object valueObject;

        for(unsigned int i = 0; i < object.via.map.size; ++i) {
            keyObject   = firstItem->key;
            valueObject = firstItem->val;

            try {
                int key = keyObject.as<int>();
                d->m_unpackerMap.at(key)->unpack(valueObject);

            } catch (...) {
                qDebug() <<  "[" << __FUNCTION__ << "]" << " convert type cath exception!";
            }
            firstItem++;
        }
    }
}

}

