#include "report_header.h"
#include <QDateTime>

namespace DplReport {

#define REPORT_VERSION     ("1.0")
#define INSPECTION_VERSION  ("1.0")

ReportHeader::ReportHeader()
    : BaseReport()
{

}

bool ReportHeader::save(lua_State *lua)
{
    m_lua = lua;
    save_header();
    return true;
}

void ReportHeader::save_header()
{
    qDebug("[%s]", __FUNCTION__);

    set_kv(m_lua, "ReportDate", m_reportDateTime);
    set_kv(m_lua, "InspectionDate", m_inspectionDateTime);
    set_kv(m_lua, "ReportVersion", REPORT_VERSION);
    set_kv(m_lua, "SetupFile", m_setupFile);
    set_kv(m_lua, "InspectionVersion", INSPECTION_VERSION);
    set_kv(m_lua, "SaveMode", m_saveMode);
    set_kv(m_lua, "DeviceType", m_deviceType);
    set_kv(m_lua, "ReportFile", ::basename(m_reportFile.toStdString().c_str()));
}

}
