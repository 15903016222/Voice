#ifndef __REPORT_LAW_H__
#define __REPORT_LAW_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

#define FOCAL_FIELDS_MAX    (4)

class ReportLaw : public BaseReport
{
public:
    ReportLaw();
    virtual bool save(lua_State *lua);

    inline void set_enable(bool flag) { m_enable = flag; }
    inline void set_element_qty(const QString &elementQty) { m_elementQty = elementQty; }
    inline void set_first_tx_element(const QString &firstTxElement) { m_firstTxElement = firstTxElement; }
    inline void set_last_tx_element(const QString &lastTxElement) { m_lastTxElement = lastTxElement; }
    inline void set_first_rx_element(const QString &firstRxElement) { m_firstRxElement = firstRxElement; }
    inline void set_last_rx_element(const QString &lastRxElement) { m_lastRxElement = lastRxElement; }
    inline void set_element_resolution(const QString &elementResolution) { m_elementResolution = elementResolution; }
    inline void set_start_angle(const QString &startAngle) { m_startAngle = startAngle; }
    inline void set_stop_angle(const QString &stopAngle) { m_stopAngle = stopAngle; }
    inline void set_angle_resolution(const QString &angleResolution) { m_angleResolution = angleResolution; }
    inline void set_type(const QString &type) { m_type = type; }
    inline void set_focal_type(const QString &focalType) { m_focalType = focalType; }

    bool set_focal_field_names(uint index, const QString &name);
    bool set_focal_field_values(uint index, const QString &value);

private:
    bool m_enable;
    QString m_elementQty;
    QString m_firstTxElement;
    QString m_lastTxElement;
    QString m_firstRxElement;
    QString m_lastRxElement;
    QString m_elementResolution;
    QString m_startAngle;
    QString m_stopAngle;
    QString m_angleResolution;
    QString m_type;
    QString m_focalType;
    QString m_focalFieldNames[FOCAL_FIELDS_MAX];
    QString m_focalFieldValues[FOCAL_FIELDS_MAX];

    void save_value();
    void save_empty_value();
};

typedef QSharedPointer<ReportLaw> ReportLawPointer;

}

#endif // __REPORT_LAW_H__
