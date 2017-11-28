#ifndef __NETWORK_MANAGER_H__
#define __NETWORK_MANAGER_H__

#include <QString>

namespace DplPreferenceMenu {

class NetworkManager
{
public:
    NetworkManager();

    /**
     * @brief get_local_ip_address 获取本地IP地址
     * @param ip    IP地址输出参数
     */
    void get_local_ip_address(QString &ip);

    /**
     * @brief set_ip_address 设置本地IP地址
     * @param newIp 待设置的IP地址
     * @return  true:设置成功；false:设置不成功
     */
    bool set_ip_address(const QString &newIp);

    /**
     * @brief get_subnet_mask 获取子网掩码
     * @param mask 子网掩码输出参数
     */
    void get_subnet_mask(QString &mask);

    /**
     * @brief set_subnet_mask 设置本机子网掩码
     * @param mask 待设置的子网掩码
     * @return  true:设置成功；false:设置不成功
     */
    bool set_subnet_mask(const QString &mask);

private:
    NetworkManager(const NetworkManager &);
    NetworkManager & operator= (const NetworkManager &);

    /**
     * @brief set_config_file_by_tag 根据设置标志，更改网络文件
     * @param tag   文件标志
     * @param info  待设置信息
     * @return
     */
    bool set_config_file_by_tag(const QString &tag, const QString &info);

};

}

#endif // __NETWORK_MANAGER_H__
