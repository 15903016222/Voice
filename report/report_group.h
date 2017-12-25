/**
 * @file    report_group.h
 * @brief   报表中组信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_GROUP_H__
#define __REPORT_GROUP_H__

#include "base_report.h"
#include <QSharedPointer>

#include "report_probe.h"
#include "report_wedge.h"
#include "report_fft.h"
#include "report_setup.h"
#include "report_law.h"
#include "report_part.h"
#include "report_scan.h"

namespace DplReport {

class ReportGroup : public BaseReport
{
public:
    ReportGroup(int id);
    virtual bool save(lua_State *lua);
    int id();

    inline const ReportProbePointer & get_probe() const { return m_probe; }
    inline const ReportWedgePointer & get_wedge() const { return m_wedge; }
    inline const ReportFFTPointer & get_fft() const     { return m_fft; }
    inline const ReportSetupPointer & get_setup() const { return m_setup; }
    inline const ReportLawPointer & get_law() const     { return m_law; }
    inline const ReportPartPointer & get_part() const   { return m_part; }
    inline const ReportScanPointer & get_scan() const   { return m_scan; }

private:
    bool save_group();
    int  m_id;

    ReportProbePointer m_probe;
    ReportWedgePointer m_wedge;
    ReportFFTPointer   m_fft;
    ReportSetupPointer m_setup;
    ReportLawPointer   m_law;
    ReportPartPointer  m_part;
    ReportScanPointer  m_scan;
};

typedef QSharedPointer<ReportGroup> ReportGroupPointer;

}

#endif // __REPORT_GROUP_H__
