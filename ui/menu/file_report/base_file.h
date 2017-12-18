#ifndef __BASE_FILE_H__
#define __BASE_FILE_H__

#include <QString>
#include <QObject>

class BaseFile : public QObject
{
    Q_OBJECT
public:
    BaseFile(QObject *parent = 0);

    /**
     * @brief save      保存文件
     * @param fileName  待保存的文件名
     * @return          true：保存成功；false：保存失败
     */
    virtual bool save(const QString &fileName) = 0;
};

#endif // __BASE_FILE_H__
