#include "report_law.h"
#include <QString>
namespace DplReport {

ReportLaw::ReportLaw()
    : BaseReport(),
      m_enable(false)
{

}

bool ReportLaw::save(lua_State *lua)
{
    qDebug("[ReportLaw::save]");

    m_lua = lua;

    if(m_enable) {
        save_value();
    } else {
        save_empty_value();
    }

    return true;
}

bool ReportLaw::set_focal_field_names(uint index, const QString &name)
{
    if(index >= FOCAL_FIELDS_MAX) {
        return false;
    }

    m_focalFieldNames[index] = name;
    return true;
}

bool ReportLaw::set_focal_field_values(uint index, const QString &value)
{
    if(index >= FOCAL_FIELDS_MAX) {
        return false;
    }

    m_focalFieldValues[index] = value;
    return true;
}

void ReportLaw::save_value()
{
    set_kv(m_lua, "ElementQty", m_elementQty);
    set_kv(m_lua, "FirstTxElement", m_firstTxElement);
    set_kv(m_lua, "LastTxElement", m_lastTxElement);
    set_kv(m_lua, "FirstRxElement", m_firstRxElement);
    set_kv(m_lua, "LastRxElement", m_lastRxElement);
    set_kv(m_lua, "ElementResolution", m_elementResolution);
    set_kv(m_lua, "StartAngle", m_startAngle);
    set_kv(m_lua, "StopAngle", m_stopAngle);
    set_kv(m_lua, "AngleResolution", m_angleResolution);
    set_kv(m_lua, "LawType", m_type);
    set_kv(m_lua, "FocalType", m_focalType);

    ::lua_pushstring(m_lua, "FocalFieldNames");
    ::lua_createtable(m_lua, 0, 0);
    for (int i = 0; i < FOCAL_FIELDS_MAX; ++i) {
        if (NULL == m_focalFieldNames[i]) {
            set_av(m_lua, i + 1, "");
        } else {
            set_av(m_lua, i + 1, m_focalFieldNames[i]);
        }
    }
    ::lua_settable(m_lua, -3);

    ::lua_pushstring(m_lua, "FocalFieldValues");
    ::lua_createtable(m_lua, 0, 0);
    for (int i = 0; i < FOCAL_FIELDS_MAX; ++i) {
        if (NULL == m_focalFieldNames[i]) {
            set_av(m_lua, i + 1, "");
        } else {
            set_av(m_lua, i + 1, m_focalFieldValues[i]);
        }
    }

    ::lua_settable(m_lua, -3);
}

void ReportLaw::save_empty_value()
{
    set_kv(m_lua, "ElementQty", "-");
    set_kv(m_lua, "FirstTxElement", "-");
    set_kv(m_lua, "LastTxElement", "-");
    set_kv(m_lua, "FirstRxElement", "-");
    set_kv(m_lua, "LastRxElement", "-");
    set_kv(m_lua, "ElementResolution", "-");
    set_kv(m_lua, "StartAngle", "-");
    set_kv(m_lua, "StopAngle", "-");
    set_kv(m_lua, "AngleResolution", "-");
    set_kv(m_lua, "LawType", "-");
    set_kv(m_lua, "FocalType", "-");

    ::lua_pushstring(m_lua, "FocalFieldNames");
    ::lua_createtable(m_lua, 0, 0);
    ::lua_settable(m_lua, -3);

    ::lua_pushstring(m_lua, "FocalFieldValues");
    ::lua_createtable(m_lua, 0, 0);
    ::lua_settable(m_lua, -3);
}

}
