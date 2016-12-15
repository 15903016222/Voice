#include "config_msg.h"

#include "msgpack.h"

#include <QCoreApplication>
#include <QDebug>

ConfigMsg::ConfigMsg()
{
    QCoreApplication::setOrganizationName(QString("Mercury"));
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
//    settings.clear();
    qDebug() << "fileName" << settings.fileName();
}

ConfigMsg::~ConfigMsg()
{

}

void ConfigMsg::add_config_msg(QString &groupName, QString &mainMenu, QString &subMenu, QVariant &variant)
{
    QVariantMap map = get_map(groupName, mainMenu);
    map.insert(subMenu, variant);

    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.beginGroup(groupName);
    settings.setValue(mainMenu, MsgPack::pack(map));
    settings.endGroup();

    map.clear();
}

void ConfigMsg::add_config_msg(QString &groupName, QString &mainMenu, QVariantMap &map)
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.beginGroup(groupName);
    settings.setValue(mainMenu, MsgPack::pack(map));
    settings.endGroup();
    map.clear();
}

QVariant ConfigMsg::get_config_msg(QString &groupName, QString &mainMenu, QString &subMenu)
{
    QVariant variant;
    QVariantMap map = get_map(groupName, mainMenu);
    if(map.contains(subMenu)) {
        variant = map.value(subMenu);
    }
    qDebug() << variant;
    map.clear();
    return variant;
}

QVariantMap ConfigMsg::get_map(QString &groupName, QString &mainMenu)
{
    QVariantMap map;
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    QVariant variant = settings.value(groupName + QString("/") + mainMenu);
    if(!variant.isNull()) {
        map = MsgPack::unpack(variant.toByteArray()).toMap();
    }
    variant.clear();
    return map;
}

void ConfigMsg::insert_msg_to_map(QVariantMap &map, QString &subMenu, QVariant &variant)
{
    map.insert(subMenu, variant);
}

void ConfigMsg::copy_config_msg(QString &groupName1, QString &groupName2)
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    QStringList keys = settings.allKeys();
    settings.beginGroup(groupName2);
    for(int i = 0; i < keys.count(); ++ i) {
        QString key = keys.at(i);
        if(key.contains(groupName1)) {
            QString mainMenu = key.right(key.length() - groupName1.length() - 1);
            QVariantMap map = get_map(groupName1, mainMenu);
            settings.setValue(mainMenu, MsgPack::pack(map));
            map.clear();
        }
    }    
    settings.endGroup();
    qDebug() << settings.allKeys();
}

void ConfigMsg::print_group_msg(QString &groupName)
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    QStringList keys = settings.allKeys();
    for(int i = 0; i < keys.count(); ++ i) {
        QString key = keys.at(i);
        if(key.contains(groupName)) {
            QString mainMenu = key.right(key.length() - groupName.length() - 1);
            QVariantMap map = get_map(groupName, mainMenu);
            qDebug() << "key" << key << map;
            map.clear();
        }
    }
}

void ConfigMsg::reset_config_msg()
{
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.clear();
}
