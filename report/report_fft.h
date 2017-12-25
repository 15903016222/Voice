/**
 * @file    report_fft.h
 * @brief   保存报表中FFT的信息。
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_FFT_H__
#define __REPORT_FFT_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportFFT : public BaseReport
{
public:
    ReportFFT();
    virtual bool save(lua_State *lua);

    inline void set_peak_freq(const QString &peakFreq) { m_peakFreq = peakFreq; }
    inline void set_lower_freq_6_dB(const QString &lowerFreq) { m_lowerFreq6dB = lowerFreq; }
    inline void set_heigher_freq_6_dB(const QString &higherFreq) { m_higherFreq6dB = higherFreq; }
    inline void set_center_freq_6_dB(const QString &centerFreq) { m_centerFreq6dB = centerFreq; }
    inline void set_band_width_6_dB(const QString &bandWidth) { m_bandwidth6dB = bandWidth; }
    inline void set_band_width_percent_6_dB(const QString &bandWidthPercent) { m_bandwidthPercent6dB = bandWidthPercent; }

    inline void set_lower_freq_20_dB(const QString &lowerFreq) { m_lowerFreq20dB = lowerFreq; }
    inline void set_heigher_freq_20_dB(const QString &higherFreq) { m_higherFreq20dB = higherFreq; }
    inline void set_center_freq_20_dB(const QString &centerFreq) { m_centerFreq20dB = centerFreq; }
    inline void set_band_width_20_dB(const QString &bandWidth) { m_bandwidth20dB = bandWidth; }
    inline void set_band_width_percent_20_dB(const QString &bandWidthPercent) { m_bandwidthPercent20dB = bandWidthPercent; }

private:
    QString m_peakFreq;
    QString m_lowerFreq6dB;
    QString m_higherFreq6dB;
    QString m_centerFreq6dB;
    QString m_bandwidth6dB;
    QString m_bandwidthPercent6dB;
    QString m_lowerFreq20dB;
    QString m_higherFreq20dB;
    QString m_centerFreq20dB;
    QString m_bandwidth20dB;
    QString m_bandwidthPercent20dB;
};

typedef QSharedPointer<ReportFFT> ReportFFTPointer;

}

#endif // __REPORT_FFT_H__
