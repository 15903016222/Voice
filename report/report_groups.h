#ifndef __REPORT_GROUPS_H__
#define __REPORT_GROUPS_H__

#include "base_report.h"
#include "report_group.h"

namespace DplReport {

class ReportGroups : public BaseReport
{
public:
    ReportGroups();
    virtual bool save(lua_State *lua);

    bool add_group(int id);
    const ReportGroupPointer &current_group() const;
    const ReportGroupPointer &get_group(int index) const;

private:
    QVector<ReportGroupPointer> m_groupVect;
    ReportGroupPointer  m_currentGroup;

};

typedef QSharedPointer<ReportGroups>  ReportGroupsPointer;

}

#endif // __REPORT_GROUPS_H__
