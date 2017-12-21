#ifndef __REPORT_HEADER_H__
#define __REPORT_HEADER_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportHeader : public BaseReport
{
public:
    ReportHeader();
    virtual bool save(lua_State *lua);

    inline void set_setup_file(const QString &setupFile) { m_setupFile = setupFile; }
    inline void set_save_mode(const QString &saveMode) { m_saveMode = saveMode; }
    inline void set_device_type(const QString &deviceType) { m_deviceType = deviceType; }
    inline void set_report_file(const QString &reportFile) { m_reportFile = reportFile; }
    inline void set_report_date_time(const QString &reportDateTime) { m_reportDateTime = reportDateTime; }
    inline void set_inspection_date_time(const QString &inspectionDateTime) { m_inspectionDateTime = inspectionDateTime; }

private:
    QString m_setupFile;            /* setup file name */
    QString m_saveMode;             /* save mode */
    QString m_deviceType;           /* device type */
    QString m_reportFile;           /* the name of report file */
    QString m_reportDateTime;       /* report datetime */
    QString m_inspectionDateTime;   /* inspection datetime */
};

typedef QSharedPointer<ReportHeader>  ReportHeaderPointer;

}

#endif // __REPORT_HEADER_H__
