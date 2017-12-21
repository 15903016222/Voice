#include "report_users.h"

namespace DplReport {

ReportUsers::ReportUsers()
    : BaseReport()
{

}

bool ReportUsers::save(lua_State *lua)
{
    m_lua = lua;
    save_users();
    return true;
}

void ReportUsers::save_users()
{
    int i = 0;
    ::lua_pushstring(m_lua, "Users");
    ::lua_createtable(m_lua, 0, 0);

    UserVect::const_iterator it = m_userVect.begin();
    while(it != m_userVect.end()) {

        ::lua_pushinteger(m_lua, ++i);
        ::lua_createtable(m_lua, 0, 0);
        set_kv(m_lua, "Name", (*it).name);
        set_kv(m_lua, "Content", (*it).content);
        ::lua_settable(m_lua, -3);

        ++it;
    }

    ::lua_settable(m_lua, -3);
}

}
