/**
 * @file    report_scan.h
 * @brief   报表中scan信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_SCAN_H__
#define __REPORT_SCAN_H__

#include "base_report.h"
#include "report_encoder.h"
#include <QSharedPointer>

namespace DplReport {

class ReportScan : public BaseReport
{
public:
    ReportScan();
    virtual bool save(lua_State *lua);

    inline void set_scan_start(const QString &scanStart) { m_scanStart = scanStart; }
    inline void set_scan_stop(const QString &scanStop) { m_scanStop = scanStop; }
    inline void set_scan_resolution(const QString &scanResolution) { m_scanResolution = scanResolution; }
    inline void set_index_start(const QString &indexStart) { m_indexStart = indexStart; }
    inline void set_index_stop(const QString &indexStop) { m_indexStop = indexStop; }
    inline void set_index_resolution(const QString &indexResolution) { m_indexResolution = indexResolution; }
    inline void set_scan_synchro(const QString &scanSynchro) { m_scanSynchro = scanSynchro; }
    inline void set_scan_speed(const QString &scanSpeed) { m_scanSpeed = scanSpeed; }

    const ReportEncoderPointer &get_encoder(ReportEncoder::E_EncoderType encoderType)const;

private:
    QString m_scanStart;
    QString m_scanStop;
    QString m_scanResolution;
    QString m_indexStart;
    QString m_indexStop;
    QString m_indexResolution;
    QString m_scanSynchro;
    QString m_scanSpeed;

    ReportEncoderPointer m_scanEncoder;
    ReportEncoderPointer m_indexEncoder;
};

typedef QSharedPointer<ReportScan> ReportScanPointer;

}

#endif // __REPORT_SCAN_H__
