#ifndef __PREFERENCE_CONFIG_H__
#define __PREFERENCE_CONFIG_H__

#include "base_item_config.h"

namespace Config {

class PreferenceConfig : public BaseItemConfig
{
public:
    PreferenceConfig(msgpack::packer<msgpack::sbuffer> *m_packer);
    virtual void pack();
    virtual bool unpack(const msgpack::v2::object &obj);
};

}

#endif // PREFERENCECONFIG_H
