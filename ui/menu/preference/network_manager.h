#ifndef __NETWORK_MANAGER_H__
#define __NETWORK_MANAGER_H__

#include <QString>
namespace DplPreferenceMenu {

class NetworkManager
{
public:
    NetworkManager();

    /**
     * @brief ip_str    获取本地IP地址字符串
     * @return ip       IP地址字符串
     */
    QString ip_str();

    /**
     * @brief set_ip    设置本地IP地址
     * @param newIp     IP地址字符串
     * @return          true:设置成功；false:设置不成功
     */
    bool set_ip(const QString &newIp);

    /**
     * @brief mask_str  获取子网掩码
     * @return          子网掩码字符串
     */
    QString mask_str();

    /**
     * @brief set_subnet_mask   设置本机子网掩码
     * @param mask              待设置的子网掩码
     * @return                  true:设置成功；false:设置不成功
     */
    bool set_mask(const QString &mask);

private:
    Q_DISABLE_COPY(NetworkManager)

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
