#ifndef __REPORT_H__
#define __REPORT_H__

#include <QString>
#include <QSharedPointer>

#include "lua.hpp"
#include "report_header.h"
#include "report_groups.h"
#include "report_users.h"
#include "report_defects.h"

namespace DplReport {

class Report : public QObject
{
    Q_OBJECT
public:
    explicit Report(QObject *parent = 0);
    ~Report();

    bool save(const QString &fileName);

    inline void set_template_file(const QString &templateFile) { m_templateFile = templateFile; }

    const ReportHeaderPointer  &report_header() const { return m_reportHeader; }
    const ReportUsersPointer   &report_users() const { return m_reportUsers; }
    const ReportGroupsPointer  &report_groups() const { return m_reportGroups; }
    const ReportDefectsPointer &report_defects() const { return m_reportDefects; }

private:

    ReportHeaderPointer        m_reportHeader;
    ReportUsersPointer         m_reportUsers;
    ReportGroupsPointer        m_reportGroups;
    ReportDefectsPointer       m_reportDefects;
    lua_State                  *m_lua;
    QString                    m_templateFile;

};

}

#endif // __REPORT_H__
