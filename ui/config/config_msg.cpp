#include "config_msg.h"

#include "msgpack.h"

#include <QCoreApplication>
#include <QDebug>

ConfigMsg::ConfigMsg()
{
    QCoreApplication::setOrganizationName(QString("Mercury"));
    QSettings settings(QSettings::NativeFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
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

void ConfigMsg::add_config_msg(QString &groupName, QString &mainMenu, QVariantMap map)
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

void ConfigMsg::insert_msg_to_map(QVariantMap map, QString &subMenu, QVariant variant)
{
    map.insert(subMenu, variant);
}
