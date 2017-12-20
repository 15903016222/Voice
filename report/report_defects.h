#ifndef __REPORT_DEFECTS_H__
#define __REPORT_DEFECTS_H__

#include "base_report.h"
#include <QSharedPointer>

namespace DplReport {

#define MAX_FIELDS  (8)

class ReportDefects : public BaseReport
{
public:
    struct S_ReportDefect{
        QString scan;      /* scan-axis position */
        QString index;     /* index-axis position */
        QString group;
        QString channel;
        QString fieldValues[MAX_FIELDS];
        QString image;
        QString comments;  /* comments about defect */
    };

    ReportDefects();
    virtual bool save(lua_State *lua);
    bool set_field_name(uint index, const QString &name);
    inline void add_defect(const S_ReportDefect &defect) { m_defectsVect.push_back(defect); }

private:
    void save_defects();
    void save_names();
    void save_defect();
    void save_field_values(const QString values[]);

    QString                    m_fieldNames[MAX_FIELDS];
    QVector<S_ReportDefect>    m_defectsVect;
};

typedef QSharedPointer<ReportDefects>  ReportDefectsPointer;

}

#endif // __REPORT_DEFECTS_H__
