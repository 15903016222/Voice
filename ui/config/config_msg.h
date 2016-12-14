#ifndef CONFIGMSG_H
#define CONFIGMSG_H

#include <QObject>
#include <QVariantMap>
#include <QSettings>

class ConfigMsg : public QObject
{
    Q_OBJECT
    
public:
    ConfigMsg();
    ~ConfigMsg();

    void add_config_msg(QString &groupName, QString &mainMenu, QString &subMenu, QVariant &variant);
    void add_config_msg(QString &groupName, QString &mainMenu, QVariantMap &map);
    void insert_msg_to_map(QVariantMap &map, QString &subMenu, QVariant &variant);

    QVariant get_config_msg(QString &groupName, QString &mainMenu, QString &subMenu);
    QVariantMap get_map(QString &groupName, QString &mainMenu);

private:

};

#endif // CONFIGMSG_H
