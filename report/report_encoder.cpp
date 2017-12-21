#include "report_encoder.h"

namespace DplReport {

ReportEncoder::ReportEncoder(E_EncoderType encoderType)
    : BaseReport(),
      m_encoderType(encoderType),
      m_enable(false)
{

}

bool ReportEncoder::save(lua_State *lua)
{
    m_lua = lua;

    switch (m_encoderType) {
        case ScanEncoder:
        {
            save_scan_encoder();
            break;
        }
        case IndexEncoder:
        {
            save_index_encoder();
            break;
        }
        default:
            break;
    }
    return true;
}

void ReportEncoder::save_scan_encoder()
{
    if(m_enable) {
        set_kv(m_lua, "ScanEncoder", m_name);
        set_kv(m_lua, "ScanEncoderType", m_type);
        set_kv(m_lua, "ScanEncoderResolution", m_resolution);
        set_kv(m_lua, "ScanPolarity", m_polarity);
    } else {
        set_kv(m_lua, "ScanEncoder", "-");
        set_kv(m_lua, "ScanEncoderType", "-");
        set_kv(m_lua, "ScanEncoderResolution", "-");
        set_kv(m_lua, "ScanPolarity", "-");
    }
}

void ReportEncoder::save_index_encoder()
{
    if(m_enable) {
        set_kv(m_lua, "IndexEncoder", m_name);
        set_kv(m_lua, "IndexEncoderType", m_type);
        set_kv(m_lua, "IndexEncoderResolution", m_resolution);
        set_kv(m_lua, "IndexPolarity", m_polarity);
    } else {
        set_kv(m_lua, "IndexEncoder", "-");
        set_kv(m_lua, "IndexEncoderType", "-");
        set_kv(m_lua, "IndexEncoderResolution", "-");
        set_kv(m_lua, "IndexPolarity", "-");
    }
}

}
