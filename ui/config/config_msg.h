#ifndef CONFIGMSG_H
#define CONFIGMSG_H

#include <QObject>
#include <QVariantMap>
#include <QFile>
#include <QReadWriteLock>

class ConfigMsg : public QObject
{
    Q_OBJECT
    
public:
    ConfigMsg();
    ~ConfigMsg();

    void add_config_msg(QString &groupName, QString &mainMenu, QString &subMenu, QVariant &variant);
    void add_config_msg(QVariantMap &map, QString &groupName, QString &mainMenu);
    void add_global_config(QString &globalMenu, QString &variant);
    void insert_msg_to_map(QVariantMap &map, QString &subMenu, QVariant &variant);         
    void copy_config_msg(QString &groupName1, QString &groupName2);


    QVariant get_config_msg(QString &groupName, QString &mainMenu, QString &subMenu);
    QVariant get_config_msg(QVariantMap &map, QString &subMenu);
    QVariantMap get_group_map(QString &groupName);
    QVariantMap get_menu_map(QString &groupName, QString &mainMenu);
    QByteArray read_config_file(QString &path);
    void write_config_file();

    int get_group_amount();

private:
    void clear_config_msg();   
    void reset_config_msg();


    QReadWriteLock lock;
    QVariantMap m_mapConfig;
    QByteArray m_array;
    QString path;
//    QFile *file;

};

#endif // CONFIGMSG_H
