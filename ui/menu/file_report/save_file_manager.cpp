#include "save_file_manager.h"
#include <configuration/configuration.h>
#include <QFile>
#include <QDebug>
#include "inspection_data_file.h"
#include "inspection_table_file.h"
#include "screen_file.h"
#include "report_file.h"

namespace DplFileReportMenu {

static const QString g_inspectionDataFile("/inspectionData/");
static const QString g_inspectionTableFile("/inspectionTable/");
static const QString g_screenFile("/screen/");
static const QString g_reportFile("/report/");
static const QString g_configFile("/configs/");

static const QString g_SDPath("/opt/mercury/");
static const QString g_USBPath("/opt/usbStorage/");
static const QString g_SSDPath("/opt/ssdStorage/");


SaveFileManager::SaveFileManager(QObject *parent) : QObject(parent)
{
    m_storageMap.insert(SD, g_SDPath);
    m_storageMap.insert(SSD, g_USBPath);
    m_storageMap.insert(USB, g_SSDPath);

    m_specificPath.insert(InspectionData, g_inspectionDataFile);
    m_specificPath.insert(InspectionTable, g_inspectionTableFile);
    m_specificPath.insert(Screen, g_screenFile);
    m_specificPath.insert(Report, g_reportFile);
    m_specificPath.insert(Setup, g_configFile);

    m_fileType << tr(".data") << tr(".table") << tr(".jpg") << tr(".html") << tr(".cfg");

    m_fileMap.insert(InspectionData, new InspectionDataFile(this));
    m_fileMap.insert(InspectionTable, new InspectionTableFile(this));
    m_fileMap.insert(Screen, new ScreenFile(this));
    m_fileMap.insert(Report, new ReportFile(this));
}

SaveFileManager::E_ResultType SaveFileManager::save(SaveFileManager::E_SaveMode mode,
                                                    SaveFileManager::E_StorageType storage,
                                                    const QString &fileName)
{
    m_mode = mode;
    m_storage = storage;

    QString truefileName = fileName;

    if(truefileName.isEmpty()) {
        return Failed;
    }

    if(!is_legal(truefileName)) {
        return InvalidName;
    }

    truefileName = m_storageMap.value(storage) + m_specificPath.value(mode) + truefileName;
    add_index(truefileName);
    truefileName += m_fileType.at(mode);

    if(mode == Setup) {
        qDebug() << truefileName;
        Config::Configuration config;
        if(!config.save_config(truefileName)) {
            return Failed;
        }
    } else {
        if(!m_fileMap.value(mode)->save(fileName)) {
            return Failed;
        }
    }

    return Success;
}

QString SaveFileManager::get_file_suffix(int type)
{
    return m_fileType.at(type);
}

QString SaveFileManager::get_file_path(int storageType, int fileType)
{
    return QString(m_storageMap.value(storageType) + m_specificPath.value(fileType));
}

bool SaveFileManager::is_legal(const QString &name)
{
    int fileNameLen = name.length() + m_fileType.at(m_mode).length();
    if((fileNameLen > NAME_MAX)
            || ((m_storageMap.value(m_storage).length() + fileNameLen) > PATH_MAX)) {
        return false;
    }
    /* 只判断 \ / : * | ? " < > 九种特殊字符 */
    QRegExp regExp(("[\\\\/:|*?\"<>]"));
    if(name.indexOf(regExp) >= 0) {
        return false;
    }
    return true;
}

void SaveFileManager::add_index(QString &fileName)
{
    QString number;
    QFile file;
    int i = -1;
    do {
        ++i;
        number.sprintf("%03d", i);
        file.setFileName(fileName + number + m_fileType.at(m_mode));
    } while(file.exists());

    fileName +=number;
}

}


