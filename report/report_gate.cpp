#include "report_gate.h"

namespace DplReport {

ReportGate::ReportGate(E_GateType type)
    : BaseReport(),
      m_type(type),
      m_enable(false)
{

}

bool ReportGate::save(lua_State *lua)
{
    if(!m_enable) {
        return true;
    }

    m_lua = lua;
    switch (m_type) {
        case Gate_A:
        {
            set_kv(lua, "GateAStart", m_start);
            set_kv(lua, "GateAWidth", m_width);
            set_kv(lua, "GateAThreshold", m_threshold);
            set_kv(lua, "GateASynchro", m_synchro);
            break;
        }
        case Gate_B:
        {
            set_kv(lua, "GateBStart", m_start);
            set_kv(lua, "GateBWidth", m_width);
            set_kv(lua, "GateBThreshold", m_threshold);
            set_kv(lua, "GateBSynchro", m_synchro);
            break;
        }
        case Gate_I:
        {
            set_kv(lua, "GateIStart", m_start);
            set_kv(lua, "GateIWidth", m_width);
            set_kv(lua, "GateIThreshold", m_threshold);
            set_kv(lua, "GateISynchro", m_synchro);
            break;
        }
        default:
            break;
    }

    return true;
}

}
