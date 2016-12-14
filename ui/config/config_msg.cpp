#include "config_msg.h"

#include "msgpack.h"

#include <QDebug>

ConfigMsg::ConfigMsg()
{

}

ConfigMsg::~ConfigMsg()
{

}

void ConfigMsg::add_config_msg(QString groupName, QString mainMenu, QString subMenu, QVariant variant)
{
//    QVariantMap map2, map3;
//    check_map(groupName, mainMenu, subMenu);

//    map3.insert(subMenu, variant);
//    map2.insert(mainMenu,map3);

    QVariantMap t_map1, t_map2;
    if(m_mapConfig.contains(groupName)) {
        t_map1 = m_mapConfig[groupName].toMap();
        if(t_map1.contains(mainMenu)) {
            t_map2 = t_map1[mainMenu].toMap();
            if(t_map2.contains(subMenu)) {
                t_map2.remove(subMenu);
            }
        }
        t_map2.insert(subMenu, variant);
        t_map1.insert(mainMenu, t_map2);
    } else {
        t_map2.insert(subMenu, variant);
        t_map1.insert(mainMenu, t_map2);
    }
    m_mapConfig.insert(groupName, t_map1);

    m_array = MsgPack::pack(m_mapConfig);
}

void ConfigMsg::check_map(QString &groupName, QString &mainMenu, QString &subMenu)
{
    QVariantMap t_map1, t_map2;
    if(m_mapConfig.contains(groupName)) {
        t_map1 = m_mapConfig[groupName].toMap();
        if(t_map1.contains(mainMenu)) {
            t_map2 = t_map1[mainMenu].toMap();
            if(t_map2.contains(subMenu)) {
                t_map2.remove(subMenu);
            }
        }
        t_map1.insert(mainMenu, t_map2);
        m_mapConfig.insert(groupName, t_map1);
    }
}

QVariant ConfigMsg::get_config_msg(QString &groupName, QString &mainMenu, QString &subMenu)
{
    QVariant variant;
    QVariantMap map = MsgPack::unpack(m_array).toMap();
    if(map.contains(groupName)) {
        QVariantMap t_map1 = map[groupName].toMap();
        if(t_map1.contains(mainMenu)) {
            QVariantMap t_map2 = t_map1[mainMenu].toMap();
            if(t_map2.contains(subMenu)) {
                variant = t_map2.value(subMenu);
            }
        }
    }
    return variant;
}

QVariantMap ConfigMsg::get_map(QString &groupName, QString &mainMenu)
{
    QVariantMap map;
    QVariantMap t_map = MsgPack::unpack(m_array).toMap();
    if(t_map.contains(groupName)) {
        QVariantMap t_map1 = t_map[groupName].toMap();
        if(t_map1.contains(mainMenu)) {
            map = t_map1[mainMenu].toMap();
        }
    }
    return map;
}

QVariant ConfigMsg::get_message(QVariantMap &map, QString &subMenu)
{
    QVariant variant;
    if(!map.isEmpty() && map.contains(subMenu)) {
        variant = map.value(subMenu);
    }
    qDebug() << variant;
    return variant;
}

void ConfigMsg::clear_config_msg()
{
    m_array.clear();
    m_mapConfig.clear();
}
