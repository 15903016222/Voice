#include "report_part.h"

namespace DplReport {

ReportPart::ReportPart()
    : BaseReport(),
      m_material("-"),
      m_geometry("-"),
      m_thickness("-")
{

}

bool ReportPart::save(lua_State *lua)
{
    m_lua = lua;
    set_kv(lua, "PartMaterial", m_material);
    set_kv(lua, "PartGeometry", m_geometry);
    set_kv(lua, "PartThickness", m_thickness);

    return true;
}

}
