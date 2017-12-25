/**
 * @file    report_applier.h
 * @brief   报表填充器，用于填充报表信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_APPLIER_H__
#define __REPORT_APPLIER_H__

#include <QObject>
#include <report/report_scan.h>
#include <report/report_law.h>
#include <focallaw/focus_cnf.h>

namespace DplDevice {
class Group;
}
namespace DplReport {
class ReportGroups;
class ReportGroup;
class Report;
}

namespace DplFileReportMenu {

class ReportApplier : public QObject
{
    Q_OBJECT
public:
    explicit ReportApplier(DplReport::Report &report, QObject *parent = 0);

    void fill(const QString &reportFile);
    inline void set_precision(uint precision) { m_precision = precision; }

private:
    DplReport::Report   &m_report;
    DplDevice::Group    *m_currentGroup;
    uint                m_precision;

    void fill_report_header(const QString &reportFile);
    void fill_report_users();
    void fill_report_groups();
    void fill_report_defects();

    void fill_report_group(DplReport::ReportGroups *reportGroups);
    void fill_report_group_probe(DplReport::ReportGroup *group);
    void fill_report_group_wedge(DplReport::ReportGroup *group);
    void fill_report_group_fft(DplReport::ReportGroup *group);
    void fill_report_group_setup(DplReport::ReportGroup *group);
    void fill_report_group_law(DplReport::ReportGroup *group);
    void fill_report_group_part(DplReport::ReportGroup *group);
    void fill_report_group_scan(DplReport::ReportGroup *group);

    void fill_encoder(DplReport::ReportScanPointer &scan, int type);
    void fill_focal_field_names(DplReport::ReportLawPointer &law, DplFocallaw::FocusCnf::Mode mode);

};

}

#endif // __REPORT_APPLIER_H__
