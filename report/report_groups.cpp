#include "report_groups.h"

namespace DplReport {

ReportGroups::ReportGroups()
    : BaseReport()
{

}

bool ReportGroups::save(lua_State *lua)
{
    qDebug("[ReportGroups::save]");

    int i = 0;
    m_lua = lua;
    ::lua_pushstring(lua, "Groups");
    ::lua_createtable(lua, 0, 0);

    QVector<ReportGroupPointer>::const_iterator it = m_groupVect.begin();
    while(it != m_groupVect.end()) {

        ::lua_pushinteger(lua, ++i);
        ::lua_createtable(lua, 0, 0);

        (*it)->save(lua);
        ++it;

        ::lua_settable(lua, -3);
    }

    ::lua_settable(lua, -3);

    return true;
}

bool ReportGroups::add_group(int id)
{
    m_groupVect.push_back(ReportGroupPointer(new ReportGroup(id)));
    m_currentGroup = m_groupVect.last();
    return true;
}


const ReportGroupPointer &ReportGroups::get_group(int index) const
{
    if (index >= m_groupVect.size()) {
        return ReportGroupPointer();
    }
    return m_groupVect[index];
}

const ReportGroupPointer &ReportGroups::current_group() const
{
    return m_currentGroup;
}

}
