#include "report.h"

#include "report.h"
#include "base_report.h"
#include "report_defects.h"
#include "report_encoder.h"
#include "report_fft.h"
#include "report_gate.h"
#include "report_groups.h"
#include "report_header.h"
#include "report_law.h"
#include "report_part.h"
#include "report_probe.h"
#include "report_setup.h"
#include "report_users.h"
#include "report_wedge.h"
#include "report_scan.h"

namespace DplReport {

static const char *s_luaFilePath = "/opt/mercury/scripts/report.lua";

Report::Report(QObject *parent)
    : QObject(parent),
    m_reportHeader(new ReportHeader()),
    m_reportUsers(new ReportUsers()),
    m_reportGroups(new ReportGroups()),
    m_reportDefects(new ReportDefects())
{

}

Report::~Report()
{

}


bool Report::save(const QString &fileName)
{
    if(fileName.isEmpty()) {
        qDebug("[%s] file name is empty.", __FUNCTION__);
        return false;
    }

    m_lua = ::luaL_newstate();
    if (NULL == m_lua) {
        qDebug("[%s] load report library failed.", __FUNCTION__);
        return false;
    }

    ::luaL_openlibs(m_lua);

    if (luaL_dofile(m_lua, s_luaFilePath) != 0 ) {
        qDebug("[%s] load report library failed nor execute failed.", __FUNCTION__);
        ::lua_close(m_lua);
        return false;
    }
    ::lua_getglobal(m_lua, "output");
    ::lua_pushstring(m_lua, m_templateFile.toStdString().c_str());
    ::lua_pushstring(m_lua, fileName.toStdString().c_str());
    ::lua_createtable(m_lua, 0, 0);

    m_reportHeader->save(m_lua);
    m_reportUsers->save(m_lua);
    m_reportGroups->save(m_lua);
    m_reportDefects->save(m_lua);

    ::lua_pcall(m_lua, 3, 0, 0);
    ::lua_close(m_lua);

    return true;
}

}
