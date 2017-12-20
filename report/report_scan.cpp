#include "report_scan.h"

namespace DplReport {

ReportScan::ReportScan()
    : BaseReport(),
      m_scanEncoder(new ReportEncoder(ReportEncoder::ScanEncoder)),
      m_indexEncoder(new ReportEncoder(ReportEncoder::IndexEncoder))
{

}

bool ReportScan::save(lua_State *lua)
{
    qDebug("[ReportScan::save]");

    m_lua = lua;

    set_kv(lua, "ScanStart", m_scanStart);
    set_kv(lua, "ScanStop", m_scanStop);
    set_kv(lua, "ScanResolution", m_scanResolution);
    set_kv(lua, "IndexStart", m_indexStart);
    set_kv(lua, "IndexStop", m_indexStop);
    set_kv(lua, "IndexResolution", m_indexResolution);
    set_kv(lua, "ScanSynchro", m_scanSynchro);
    set_kv(lua, "ScanSpeed", m_scanSpeed);

    m_scanEncoder->save(lua);
    m_indexEncoder->save(lua);

    return true;
}

const ReportEncoderPointer &ReportScan::get_encoder(ReportEncoder::E_EncoderType encoderType) const
{
    if(encoderType == ReportEncoder::ScanEncoder) {
        return m_scanEncoder;
    } else {
        return m_indexEncoder;
    }
}

}
