/**
 * @file    report_gate.h
 * @brief   报表中闸门的信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_GATE_H__
#define __REPORT_GATE_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportGate : public BaseReport
{
public:

    enum E_GateType {
        Gate_A,
        Gate_B,
        Gate_I
    };

    ReportGate(E_GateType type);
    virtual bool save(lua_State *lua);

    inline void set_enable(bool flag) { m_enable = flag; }
    inline void set_start(const QString &start) { m_start = start; }
    inline void set_width(const QString &width) { m_width = width; }
    inline void set_threshold(const QString &threshold) { m_threshold = threshold; }
    inline void set_synchro(const QString &synchro) { m_synchro = synchro; }

private:

    E_GateType m_type;
    QString m_start;
    QString m_width;
    QString m_threshold;
    QString m_synchro;
    bool    m_enable;
};

typedef QSharedPointer<ReportGate> ReportGatePointer;

}

#endif // __REPORT_GATE_H__
