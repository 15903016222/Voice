#include "report_setup.h"

namespace DplReport {

ReportSetup::ReportSetup()
    : BaseReport(),
      m_gateA(new ReportGate(ReportGate::Gate_A)),
      m_gateB(new ReportGate(ReportGate::Gate_B)),
      m_gateI(new ReportGate(ReportGate::Gate_I))
{

}

bool ReportSetup::save(lua_State *lua)
{
    qDebug("[ReportSetup::save]");

    m_lua = lua;

    set_kv(lua, "BeamDelay", m_beamDelay);
    set_kv(lua, "HalfPathStart", m_halfPathStart);
    set_kv(lua, "HalfPathRange", m_halfPathRange);
    set_kv(lua, "PRF", m_prf);
    set_kv(lua, "InspectionType",  m_inspectionType);
    set_kv(lua, "AveragingFactor", m_averagingFactor);
    set_kv(lua, "ScaleFactor", m_scaleFactor);
    set_kv(lua, "VideoFilter", m_videoFilter);
    set_kv(lua, "Rectification", m_rectification);
    set_kv(lua, "BandPassFilter", m_bandPassFilter);
    set_kv(lua, "Voltage", m_voltage);
    set_kv(lua, "Gain", m_gain);
    set_kv(lua, "RxTxMode", m_rxTxMode);
    set_kv(lua, "WaveType", m_waveType);
    set_kv(lua, "SoundVelocity", m_soundVelocity);
    set_kv(lua, "PulseWidth", m_pulseWidth);
    set_kv(lua, "ScanOffset", m_scanOffset);
    set_kv(lua, "IndexOffset", m_indexOffset);
    set_kv(lua, "Skew", m_skew);

    m_gateA->save(lua);
    m_gateB->save(lua);
    m_gateI->save(lua);

    return true;
}

const ReportGatePointer &ReportSetup::get_gate(ReportGate::E_GateType type) const
{
    switch (type) {
    case ReportGate::Gate_A:
    {
        return m_gateA;
        break;
    }
    case ReportGate::Gate_B:
    {
        return m_gateB;
        break;
    }
    case ReportGate::Gate_I:
    {
        return m_gateI;
        break;
    }
    default:
        break;
    }
}

}
