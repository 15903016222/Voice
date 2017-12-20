#ifndef __REPORT_SETUP_H__
#define __REPORT_SETUP_H__

#include "base_report.h"
#include "report_gate.h"
#include <QSharedPointer>

namespace DplReport {

class ReportSetup : public BaseReport
{
public:

    ReportSetup();
    virtual bool save(lua_State *lua);
    inline void set_beam_delay(const QString &beamDelay) { m_beamDelay = beamDelay; }
    inline void set_half_path_start(const QString &halfPathStart) { m_halfPathStart = halfPathStart; }
    inline void set_half_path_range(const QString &halfPathRange) { m_halfPathRange = halfPathRange; }
    inline void set_prf(const QString &prf) { m_prf = prf; }
    inline void set_inspection_type(const QString &inspectionType) { m_inspectionType = inspectionType; }
    inline void set_averaging_factor(const QString &averagingFactor) { m_averagingFactor = averagingFactor; }
    inline void set_scale_factor(const QString &scaleFactor) { m_scaleFactor = scaleFactor; }
    inline void set_video_filter(const QString &videoFilter) { m_videoFilter = videoFilter; }
    inline void set_rectification(const QString &rectification) { m_rectification = rectification; }
    inline void set_band_pass_filter(const QString &bandPassFilter) { m_bandPassFilter = bandPassFilter; }
    inline void set_voltage(const QString &voltage) { m_voltage = voltage; }
    inline void set_gain(const QString &gain) { m_gain = gain; }
    inline void set_rx_tx_mode(const QString &rxTxMode) { m_rxTxMode = rxTxMode; }
    inline void set_wave_type(const QString &waveType) { m_waveType = waveType; }
    inline void set_sound_velocity(const QString &soundVelocity) { m_soundVelocity = soundVelocity; }
    inline void set_pulse_width(const QString &pulseWidth) { m_pulseWidth = pulseWidth; }
    inline void set_scan_offset(const QString &scanOffset) { m_scanOffset = scanOffset; }
    inline void set_index_offset(const QString &indexOffset) { m_indexOffset = indexOffset; }
    inline void set_skew(const QString &skew) { m_skew = skew; }

    const ReportGatePointer &get_gate(ReportGate::E_GateType type) const;

private:
    QString m_beamDelay;
    QString m_halfPathStart;
    QString m_halfPathRange;
    QString m_prf;
    QString m_inspectionType;
    QString m_averagingFactor;
    QString m_scaleFactor;
    QString m_videoFilter;
    QString m_rectification;
    QString m_bandPassFilter;
    QString m_voltage;
    QString m_gain;
    QString m_rxTxMode;
    QString m_waveType;
    QString m_soundVelocity;
    QString m_pulseWidth;
    QString m_scanOffset;
    QString m_indexOffset;
    QString m_skew;

    ReportGatePointer m_gateA;
    ReportGatePointer m_gateB;
    ReportGatePointer m_gateI;
};

typedef QSharedPointer<ReportSetup> ReportSetupPointer;

}

#endif // __REPORT_SETUP_H__
