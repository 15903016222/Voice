#ifndef __REPORT_PROBE_H__
#define __REPORT_PROBE_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportProbe : public BaseReport
{
public:
    ReportProbe();
    virtual bool save(lua_State *lua);

    inline void set_model(const QString &model) { m_model = model; }
    inline void set_serial(const QString &serial) { m_serial = serial; }
    inline void set_freq(const QString &freq) { m_freq = freq; }
    inline void set_aperture(const QString &aperture) { m_aperture = aperture; }

private:
    QString m_model;
    QString m_serial;
    QString m_freq;
    QString m_aperture;
};

typedef QSharedPointer<ReportProbe> ReportProbePointer;

}

#endif // __REPORT_PROBE_H__
