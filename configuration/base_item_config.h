#ifndef __BASE_ITEM_CONFIG_H__
#define __BASE_ITEM_CONFIG_H__

#include "msgpack.hpp"
#include "configuration.h"

namespace Config {

typedef std::map<int, msgpack::object>  MetaItem;
typedef std::map<int, MetaItem>         SubItemMap;

class BaseItemConfig
{
public:
    BaseItemConfig(msgpack::packer<msgpack::sbuffer> *packer);

    /**
     * @brief pack 配置文件打包
     */
    virtual void pack() = 0;

    /**
     * @brief unpack    解包配置文件
     * @param obj       待解包的对象
     * @return
     */
    virtual bool unpack(const msgpack::object &obj) = 0;

protected:
    msgpack::packer<msgpack::sbuffer> *m_packer;
};

}

#endif // __BASE_ITEM_CONFIG_H__
