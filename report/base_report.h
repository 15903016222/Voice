#ifndef __BASE_REPORT_H__
#define __BASE_REPORT_H__

#include <QDebug>

#include <lua.hpp>

namespace DplReport {

class BaseReport
{
public:
    BaseReport();
    virtual ~BaseReport();

    virtual bool save(lua_State *lua) = 0;

    inline lua_State *get_lua() { return m_lua; }

protected:
    lua_State   *m_lua;

    void set_kv(lua_State *L, const QString &key, const QString &val);
    void set_av(lua_State *L, int index, const QString &val);
};

}

#endif // __BASE_REPORT_H__
