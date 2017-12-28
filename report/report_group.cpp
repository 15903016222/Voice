#include "report_group.h"

namespace DplReport {

ReportGroup::ReportGroup(int id)
    : m_id(id),
      m_probe(new ReportProbe),
      m_wedge(new ReportWedge),
      m_fft(new ReportFFT),
      m_setup(new ReportSetup),
      m_law(new ReportLaw),
      m_part(new ReportPart),
      m_scan(new ReportScan)
{

}


bool ReportGroup::save(lua_State *lua)
{
    m_lua = lua;

    m_probe->save(lua);
    m_wedge->save(lua);
    m_fft->save(lua);
    m_setup->save(lua);
    m_law->save(lua);
    m_part->save(lua);
    m_scan->save(lua);

    return true;
}

int ReportGroup::id()
{
    return m_id;
}

}
