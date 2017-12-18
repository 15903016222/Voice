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

    E_ResultType save(E_SaveMode mode, E_StorageType storage, const QString &fileName);
    QString     get_file_suffix(int type);
    QString     get_file_path(int storageType, int fileType);

private:


    ListMap         m_storageMap;
    ListMap         m_specificPath;
    QStringList     m_fileType;
    E_SaveMode      m_mode;
    E_StorageType   m_storage;
    FileMap         m_fileMap;

    bool is_legal(const QString &name);
    void add_index(QString &fileName);

};
}

#endif // __SAVE_FILE_MANAGER_H__
