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

    virtual void pack() = 0;
    virtual void unpack(const msgpack::object &obj) = 0;

protected:
    msgpack::packer<msgpack::sbuffer> *m_packer;
};

}

#endif // __BASE_ITEM_CONFIG_H__
