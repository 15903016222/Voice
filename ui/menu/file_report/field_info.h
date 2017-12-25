#ifndef __FIELD_INFO_H__
#define __FIELD_INFO_H__

#include <QObject>
#include <device/group.h>

namespace DplFileReportMenu {

typedef QMap<QObject*, QString> FieldNameMap;

class FieldInfo : public QObject
{
    Q_OBJECT
public:
    explicit FieldInfo(QObject *parent = 0);
    static FieldInfo *instance();

    bool add_field_names(const DplDevice::GroupPointer &group, const FieldNameMap &nameMap);
    QList<QString> field_names(const DplDevice::GroupPointer &group);
    bool set_field_name(const DplDevice::GroupPointer &group, QObject *obj, const QString &fieldName);

public slots:
    void do_group_qty_changed(int index);
private:
    static FieldInfo *s_instance;
    QMap<int, FieldNameMap> m_fieldNamesMap;
};

}

#endif // __FIELD_INFO_H__
