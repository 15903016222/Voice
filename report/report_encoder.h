/**
 * @file    report_encoder.h
 * @brief   保存报表中encoder的信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_ENCODER_H__
#define __REPORT_ENCODER_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportEncoder : public BaseReport
{
public:
    enum E_EncoderType {
        ScanEncoder,
        IndexEncoder
    };

    ReportEncoder(E_EncoderType encoderType);
    virtual bool save(lua_State *lua);

    inline void set_enable(bool flag) { m_enable = flag; }
    inline void set_name(const QString &name) { m_name = name; }
    inline void set_type(const QString &type) { m_type = type; }
    inline void set_resolution(const QString &resolution) { m_resolution = resolution; }
    inline void set_polarity(const QString &polarity) { m_polarity = polarity; }

private:
    E_EncoderType m_encoderType;
    bool    m_enable;
    QString m_name;
    QString m_type;
    QString m_resolution;
    QString m_polarity;

    void save_scan_encoder();
    void save_index_encoder();

};

typedef QSharedPointer<ReportEncoder> ReportEncoderPointer;

}

#endif // __REPORT_ENCODER_H__
