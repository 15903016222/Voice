#include "report_defects.h"

namespace DplReport {

ReportDefects::ReportDefects()
    : BaseReport()
{

}

bool ReportDefects::save(lua_State *lua)
{
    m_lua = lua;
    save_defects();
    return true;
}

bool ReportDefects::set_field_name(uint index, const QString &name)
{
    if(index >= MAX_FIELDS) {
        return false;
    }

    m_fieldNames[index] = name;
    return true;
}

void ReportDefects::save_defects()
{
    save_names();
    save_defect();
}

void ReportDefects::save_names()
{
    ::lua_pushstring(m_lua, "FieldNames");
    ::lua_createtable(m_lua, 0, 0);

    for (int i = 0; i < MAX_FIELDS; ++i) {
        set_av(m_lua, i + 1, m_fieldNames[i]);
    }

    ::lua_settable(m_lua, -3);
}

void ReportDefects::save_defect()
{
    ::lua_pushstring(m_lua, "Defects");
    ::lua_createtable(m_lua, 0, 0);

    QVector<S_ReportDefect>::const_iterator it = m_defectsVect.begin();
    int i = 0;
    while(it != m_defectsVect.end()) {

        ::lua_pushinteger(m_lua, ++i);
        ::lua_createtable(m_lua, 0, 0);

        set_kv(m_lua, "Scan", (*it).scan);
        set_kv(m_lua, "Index", (*it).index);
        set_kv(m_lua, "Group", (*it).group);
        set_kv(m_lua, "Channel", (*it).channel);

        if (!(*it).image.isEmpty()) {
            set_kv(m_lua, "Image", (*it).image);
        }

        save_field_values((*it).fieldValues);

        ::lua_settable(m_lua, -3);

        ++it;
    }

    ::lua_settable(m_lua, -3);
}

void ReportDefects::save_field_values(const QString values[])
{
    ::lua_pushstring(m_lua, "FieldValues");
    ::lua_createtable(m_lua, 0, 0);

    for(int i = 0; i < MAX_FIELDS; ++i) {
        set_av(m_lua, i + 1, values[i]);
    }

    ::lua_settable(m_lua, -3);
}

}
