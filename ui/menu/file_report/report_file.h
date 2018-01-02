/**
 * @file    report_file.h
 * @brief   报表文件，用于保存报表。
 * @author  Jinhua Zhang <zhangjinhua@cndoppler.cn>
 * @version 0.1
 * @date    2017-12-25
 */

#ifndef __REPORT_FILE_H__
#define __REPORT_FILE_H__

#include "base_file.h"

class ReportFile : public BaseFile
{
    Q_OBJECT
public:
    explicit ReportFile(QObject *parent = 0);

    /**
     * @brief save      保存Report文件
     * @param fileName  待保存的文件名
     * @return          true：保存成功；false：保存失败
     */
    virtual bool save(const QString &fileName);
};

#endif // __REPORT_FILE_H__
