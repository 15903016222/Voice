#ifndef __REPORT_WEDGE_H__
#define __REPORT_WEDGE_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportWedge : public BaseReport
{
public:
    ReportWedge();
    virtual bool save(lua_State *lua);

    inline void set_model(const QString &model) { m_model = model; }
    inline void set_angle(const QString &angle) { m_angle = angle; }

private:
    QString m_model;
    QString m_angle;
};

typedef QSharedPointer<ReportWedge> ReportWedgePointer;

}

#endif // __REPORT_WEDGE_H__
