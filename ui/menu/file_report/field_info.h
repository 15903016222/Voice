/**
 * @file    field_info.h
 * @brief   域信息类，用于保存当前组域信息
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

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

    /**
     * @brief add_field_names   添加域信息
     * @param group             组
     * @param nameMap           域名称键值对
     * @return                  true：添加成功； false：添加失败
     */
    bool add_field_names(const DplDevice::GroupPointer &group, const FieldNameMap &nameMap);

    /**
     * @brief field_names       获取指定组的域信息
     * @param group             组
     * @return                  返回域名列表
     */
    QList<QString> field_names(const DplDevice::GroupPointer &group);

    /**
     * @brief set_field_name    设置域名称
     * @param group             指定的组
     * @param obj               保存域名的控件
     * @param fieldName         域名称
     * @return
     */
    bool set_field_name(const DplDevice::GroupPointer &group, QObject *obj, const QString &fieldName);

public slots:
    void do_group_qty_changed(int index);

private:
    static FieldInfo *s_instance;
    QMap<int, FieldNameMap> m_fieldNamesMap;
};

}

#endif // __FIELD_INFO_H__
