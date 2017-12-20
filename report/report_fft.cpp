#include "report_fft.h"

namespace DplReport {

ReportFFT::ReportFFT()
    : BaseReport()
{

}

bool ReportFFT::save(lua_State *lua)
{
    qDebug("[ReportFFT::save]");

    m_lua = lua;
    set_kv(lua, "PeakFreq", m_peakFreq);
    set_kv(lua, "LowerFreq_6dB", m_lowerFreq6dB);
    set_kv(lua, "HigherFreq_6dB", m_higherFreq6dB);
    set_kv(lua, "CenterFreq_6dB", m_centerFreq6dB);
    set_kv(lua, "Bandwidth_6dB", m_bandwidth6dB);
    set_kv(lua, "BandwidthPercent_6dB", m_bandwidthPercent6dB);
    set_kv(lua, "LowerFreq_20dB", m_lowerFreq20dB);
    set_kv(lua, "HigherFreq_20dB", m_higherFreq20dB);
    set_kv(lua, "CenterFreq_20dB", m_centerFreq20dB);
    set_kv(lua, "Bandwidth_20dB", m_bandwidth20dB);
    set_kv(lua, "BandwidthPercent_20dB", m_bandwidthPercent20dB);
    return true;
}

}

