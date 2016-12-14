#ifndef CONFIGMSG_H
#define CONFIGMSG_H

#include <QObject>
#include <QVariantMap>

class ConfigMsg : public QObject
{
    Q_OBJECT
    
public:
    ConfigMsg();
    ~ConfigMsg();

    void add_config_msg(QString groupName, QString mainMenu, QString subMenu, QVariant variant);
    void check_map(QString &groupName, QString &mainMenu, QString &subMenu);
    QVariant get_config_msg(QString &groupName, QString &mainMenu, QString &subMenu);
    QVariantMap get_map(QString &groupName, QString &mainMenu);
    QVariant get_message(QVariantMap map, QString &subMenu);
    void clear_config_msg();

private:
    QVariantMap m_mapConfig;
    QByteArray m_array;

};

#endif // CONFIGMSG_H
