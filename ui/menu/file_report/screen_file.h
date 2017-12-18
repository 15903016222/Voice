#ifndef __SCREEN_FILE_H__
#define __SCREEN_FILE_H__

#include "base_file.h"

class ScreenFile : public BaseFile
{
    Q_OBJECT
public:
    explicit ScreenFile(QObject *parent = 0);

    /**
     * @brief save      保存Screen文件
     * @param fileName  待保存的文件名
     * @return          true：保存成功；false：保存失败
     */
    virtual bool save(const QString &fileName);
};

#endif // __SCREEN_FILE_H__
