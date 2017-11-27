#include "configuration.h"

#include "msgpack.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <QString>
#include <QDebug>

namespace Config {

Configuration::Configuration()
{
    std::vector<std::string> _vecString;
    _vecString.push_back("Hello");
    _vecString.push_back("world");

    // pack
    msgpack::sbuffer _sbuffer;
    msgpack::pack(_sbuffer, _vecString);
    std::cout << _sbuffer.data() << std::endl;

    // unpack
    msgpack::unpacked msg;
    msgpack::unpack(msg, _sbuffer.data(), _sbuffer.size());
    msgpack::object obj = msg.get();
    std::cout << obj << std::endl;

    // convert
    std::vector<std::string> _vecRString;
    obj.convert(_vecRString);

    // print
    for(size_t i = 0; i < _vecRString.size(); ++i)
    {
        std::cout << _vecRString[i] << std::endl;
    }
}

}

