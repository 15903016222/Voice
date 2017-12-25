#include "report_probe.h"

namespace DplReport {

ReportProbe::ReportProbe()
    : BaseReport(),
      m_model("-"),
      m_serial("-"),
      m_freq("-"),
      m_aperture("-")
{

}

bool ReportProbe::save(lua_State *lua)
{
    m_lua = lua;
    set_kv(lua, "ProbeModel", m_model);
    set_kv(lua, "ProbeSerial", m_serial);
    set_kv(lua, "ProbeFreq", m_freq);
    set_kv(lua, "ProbeAperture", m_aperture);
    return true;
}

}
