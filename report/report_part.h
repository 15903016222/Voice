#ifndef __REPORT_PART_H__
#define __REPORT_PART_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportPart : public BaseReport
{
public:
    ReportPart();
    virtual bool save(lua_State *lua);

    inline void set_material(const QString &material) { m_material = material; }
    inline void set_geometry(const QString &geometry) { m_geometry = geometry; }
    inline void set_thickness(const QString &thickness) { m_thickness = thickness; }

private:
    QString m_material;
    QString m_geometry;
    QString m_thickness;
};

typedef QSharedPointer<ReportPart> ReportPartPointer;

}

#endif // __REPORT_PART_H__
