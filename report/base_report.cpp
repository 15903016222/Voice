#include "base_report.h"

namespace DplReport {

BaseReport::BaseReport() :
    m_lua(NULL)
{

}

BaseReport::~BaseReport()
{
}

void BaseReport::set_kv(lua_State *L, const QString &key, const QString &val)
{
    ::lua_pushstring(L, key.toStdString().c_str());
    if (val.isEmpty()) {
        lua_pushstring(L, "-");
    } else {
        lua_pushstring(L, val.toStdString().c_str());
    }
    ::lua_settable(L, -3);
}

void BaseReport::set_av(lua_State *L, int index, const QString &val)
{
    ::lua_pushinteger(L, index);
    if (val.isEmpty()) {
        ::lua_pushstring(L, "-");
    } else {
        ::lua_pushstring(L, val.toStdString().c_str());
    }
    ::lua_settable(L, -3);
}

}
