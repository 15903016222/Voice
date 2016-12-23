#include "config_msg.h"

#include "msgpack.h"

#include <sys/time.h>

#include <QFile>
#include <QVariant>
#include <QDataStream>
#include <QReadWriteLock>
#include <QDebug>

ConfigMsg::ConfigMsg()
{
    path = "Mercury.conf";
    m_array = read_config_file(path);
    m_mapConfig = MsgPack::unpack(m_array).toMap();
    qDebug() << m_array;
    qDebug() << m_mapConfig;
}

ConfigMsg::~ConfigMsg()
{
    clear_config_msg();
}

void ConfigMsg::add_config_msg(QString &groupName, QString &mainMenu, QString &subMenu, QVariant &variant)
{
    QVariantMap t_map1, t_map2;
    if(m_mapConfig.contains(groupName)) {
        t_map1 = m_mapConfig[groupName].toMap();
        if(t_map1.contains(mainMenu)) {
            t_map2 = t_map1[mainMenu].toMap();
//            if(t_map2.contains(subMenu)) {
//                t_map2.remove(subMenu);
//            }
        }
        t_map2.insert(subMenu, variant);
        t_map1.insert(mainMenu, t_map2);
    } else {
        t_map2.insert(subMenu, variant);
        t_map1.insert(mainMenu, t_map2);
    }
    m_mapConfig.insert(groupName, t_map1);

    m_array = MsgPack::pack(m_mapConfig);
    qDebug() << m_array;
    qDebug() << m_mapConfig;
}

void ConfigMsg::add_config_msg(QVariantMap &map, QString &groupName, QString &mainMenu)
{
    QVariantMap t_map = get_menu_map(groupName, mainMenu);
    t_map.insert(mainMenu, map);
    m_mapConfig.insert(groupName, t_map);
    m_array = MsgPack::pack(m_mapConfig);
}

void ConfigMsg::add_global_config(QString &globalMenu, QString &variant)
{
    m_mapConfig.insert(globalMenu, variant);
    m_array = MsgPack::pack(m_mapConfig);
}

void ConfigMsg::insert_msg_to_map(QVariantMap &map, QString &subMenu, QVariant &variant)
{
    map.insert(subMenu, variant);
}

QVariant ConfigMsg::get_config_msg(QString &groupName, QString &mainMenu, QString &subMenu)
{
    QVariant variant;
    QVariantMap mainMenuMap = get_menu_map(groupName, mainMenu);
    qDebug() << mainMenuMap;
    if(!mainMenuMap.isEmpty() && mainMenuMap.contains(subMenu)) {
        variant = mainMenuMap.value(subMenu);
    }
    qDebug() << variant;
    return variant;
}

QVariantMap ConfigMsg::get_group_map(QString &groupName)
{
    QVariantMap t_map = MsgPack::unpack(m_array).toMap();
    return t_map[groupName].toMap();
}

QVariantMap ConfigMsg::get_menu_map(QString &groupName, QString &mainMenu)
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

QVariant ConfigMsg::get_config_msg(QVariantMap &map, QString &subMenu)
{
    QVariant variant;
    if(!map.isEmpty() && map.contains(subMenu)) {
        variant = map.value(subMenu);
    }
    qDebug() << "get_config_msg" << variant;
    return variant;
}

void ConfigMsg::clear_config_msg()
{
    m_array.clear();
    m_mapConfig.clear();
}

QByteArray ConfigMsg::read_config_file(QString &path)
{
    lock.lockForRead();
    QFile *file = new QFile(path);
    if(!file->open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open the file.";
    }
    QByteArray array = file->readAll();
    file->close();
    lock.unlock();
    return array.right(array.length() - 4);
}

void ConfigMsg::write_config_file()
{
    lock.lockForWrite();
    QFile *file = new QFile(path);
    file->open(QIODevice::ReadWrite);
    QDataStream in(file);
    in.setVersion(QDataStream::Qt_4_8);
    in << m_array;
    file->close();
    lock.unlock();
}

void ConfigMsg::copy_config_msg(QString &groupName1, QString &groupName2)
{
    QVariantMap t_map;
    if(m_mapConfig.contains(groupName1)) {
        t_map = m_mapConfig[groupName1].toMap();
    }
    m_mapConfig.insert(groupName2, t_map);
}

void ConfigMsg::reset_config_msg()
{
//    m_mapConfig.clear();
//    m_array.clear();
}

int ConfigMsg::get_group_amount()
{
    int amount = 0;
    foreach (QString str, m_mapConfig.keys()) {
        if(!m_mapConfig.value(str).toMap().isEmpty()) {
            amount += 1;
        }
    }
    qDebug() << "amount" << amount;
    return amount;
}
