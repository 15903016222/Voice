#ifndef __REPORT_FILE_H__
#define __REPORT_FILE_H__

#include "base_file.h"

class ReportFile : public BaseFile
{
    Q_OBJECT
public:
    explicit ReportFile(QObject *parent = 0);

    virtual bool save(const QString &fileName);
};

#endif // __REPORT_FILE_H__
