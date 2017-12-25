#include "field_info.h"
#include <device/device.h>

namespace DplFileReportMenu {

FieldInfo *FieldInfo::s_instance = NULL;

FieldInfo::FieldInfo(QObject *parent) : QObject(parent)
{
    connect(DplDevice::Device::instance(), SIGNAL(group_qty_changed(int)),
            this, SLOT(do_group_qty_changed(int)));
}

FieldInfo *FieldInfo::instance()
{
    if(NULL == s_instance) {
        s_instance = new FieldInfo();
    }
    return s_instance;
}

bool FieldInfo::add_field_names(const DplDevice::GroupPointer &group, const FieldNameMap &nameMap)
{
    if(group.isNull()) {
        return false;
    }

    m_fieldNamesMap.insert(group->index(), nameMap);
    return true;
}

QList<QString> FieldInfo::field_names(const DplDevice::GroupPointer &group)
{
    if(group.isNull()) {
        return QStringList();
    }

    return m_fieldNamesMap.value(group->index()).values();
}

bool FieldInfo::set_field_name(const DplDevice::GroupPointer &group, QObject *obj, const QString &fieldName)
{
    if(group.isNull()) {
        return false;
    }

    FieldNameMap nameMap = m_fieldNamesMap.value(group->index());
    nameMap.insert(obj, fieldName);
    m_fieldNamesMap.insert(group->index(), nameMap);
    return true;
}

void FieldInfo::do_group_qty_changed(int index)
{
    if(index > m_fieldNamesMap.count()) {
        FieldNameMap nameMap = m_fieldNamesMap.value(DplDevice::Device::instance()->current_group()->index());
        m_fieldNamesMap.insert(index, nameMap);
    } else {
        m_fieldNamesMap.remove(index);
    }
}

}
