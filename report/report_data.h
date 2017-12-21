#ifndef __REPORT_DATA_H__
#define __REPORT_DATA_H__

#include <QObject>
#include "report_scan.h"

namespace DplDevice {
class Group;
}

namespace DplReport {

class ReportGroups;
class ReportGroup;
class Report;

class ReportData : public QObject
{
    Q_OBJECT
public:
    explicit ReportData(Report *report, QObject *parent = 0);

    void fill(const QString &reportFile);

private:
    Report *m_report;
    DplDevice::Group    *m_currentGroup;

    void fill_report_header(const QString &reportFile);
    void fill_report_users();
    void fill_report_groups();
    void fill_report_defects();

    void fill_report_group(ReportGroups *reportGroups);
    void fill_report_group_probe(ReportGroup *group);
    void fill_report_group_wedge(ReportGroup *group);
    void fill_report_group_fft(ReportGroup *group);
    void fill_report_group_setup(ReportGroup *group);
    void fill_report_group_law(ReportGroup *group);
    void fill_report_group_part(ReportGroup *group);
    void fill_report_group_scan(ReportGroup *group);

    void fill_encoder(ReportScanPointer &scan, int type);

};

}

#endif // __REPORT_DATA_H__
