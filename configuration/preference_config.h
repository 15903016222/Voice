#ifndef __PREFERENCE_CONFIG_H__
#define __PREFERENCE_CONFIG_H__

#include "base_item_config.h"

namespace Config {

class PreferenceConfig : public BaseItemConfig
{
public:
    PreferenceConfig(msgpack::packer<msgpack::sbuffer> *m_packer);

    /**
     * @brief pack 配置文件打包
     */
    virtual void pack();

    /**
     * @brief unpack    解包配置文件
     * @param obj       待解包的对象
     * @return
     */
    virtual bool unpack(const msgpack::v2::object &obj);
};

}

#endif // PREFERENCECONFIG_H
