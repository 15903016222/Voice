/**
 * @file    report_users.h
 * @brief   报表中的用户信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_USERS_H__
#define __REPORT_USERS_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

class ReportUsers : public BaseReport
{
public:
    struct S_USER {
        QString name;
        QString content;
    };

    typedef QVector<S_USER> UserVect;

    ReportUsers();
    virtual bool save(lua_State *lua);

    inline void add_user(const ReportUsers::S_USER &user) { m_userVect.push_back(user); }

private:
    void save_users();
    UserVect    m_userVect;
};

typedef QSharedPointer<ReportUsers>  ReportUsersPointer;

}

#endif // __REPORT_USERS_H__
