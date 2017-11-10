#ifndef __NETWORK_MANAGER_H__
#define __NETWORK_MANAGER_H__

#include <QString>

class NetworkManager
{
public:
    NetworkManager();

    void get_local_ip_address(QString &ip);
    bool set_ip_address(const QString &newIp);

    void get_subnet_mask(QString &mask);
    bool set_subnet_mask(const QString &mask);

private:
    NetworkManager(const NetworkManager &);
    NetworkManager & operator= (const NetworkManager &);

    bool set_config_file_by_tag(const QString &tag, const QString &info);

};

#endif // __NETWORK_MANAGER_H__
