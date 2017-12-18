#ifndef __SAVE_FILE_MANAGER_H__
#define __SAVE_FILE_MANAGER_H__

#include <QObject>
#include <QMap>
#include <QStringList>
#include "base_file.h"

namespace DplFileReportMenu {

class SaveFileManager : public QObject
{
    Q_OBJECT
public:

    enum E_SaveMode {
        InspectionData,
        InspectionTable,
        Screen,
        Report,
        Setup
    };

    enum E_StorageType {
        SD,
        SSD,
        USB
    };

    explicit SaveFileManager(QObject *parent = 0);

    enum E_ResultType {
        InvalidName,
        Failed,
        Success
    };

    typedef QMap<int, QString>  ListMap;
    typedef QMap<int, BaseFile*> FileMap;

    /**
     * @brief save      保存文件
     * @param mode      保存的文件类型
     * @param storage   保存的位置（SD、SSD、USB）
     * @param fileName  待保存的文件名
     * @return
     */
    E_ResultType save(E_SaveMode mode, E_StorageType storage, const QString &fileName);

    /**
     * @brief get_file_suffix   获取文件后缀
     * @param type              文件类型
     * @return
     */
    QString     get_file_suffix(int type);

    /**
     * @brief get_file_path 获取指定路径
     * @param storageType   保存位置
     * @param fileType      文件类型
     * @return
     */
    QString     get_file_path(int storageType, int fileType);

private:
    ListMap         m_storageMap;
    ListMap         m_specificPath;
    QStringList     m_fileType;
    E_SaveMode      m_mode;
    E_StorageType   m_storage;
    FileMap         m_fileMap;

    /**
     * @brief is_legal  判断文件名是否合法
     * @param name      待判断的文件名
     * @return          true：合法文件名；false：非法的文件名
     */
    bool is_legal(const QString &name);

    /**
     * @brief add_index 添加文件序号
     * @param fileName  待添加序号的文件名
     */
    void add_index(QString &fileName);

};
}

#endif // __SAVE_FILE_MANAGER_H__
