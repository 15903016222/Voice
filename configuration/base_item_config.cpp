#include "base_item_config.h"

namespace Config {

BaseItemConfig::BaseItemConfig(msgpack::packer<msgpack::sbuffer> *packer)
    : m_packer(packer)
{

}

}

