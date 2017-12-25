/**
 * @file    report_part.h
 * @brief   报表中工件信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

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
