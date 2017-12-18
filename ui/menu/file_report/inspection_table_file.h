#ifndef __INSPECTION_TABLE_FILE_H__
#define __INSPECTION_TABLE_FILE_H__

#include "base_file.h"

class InspectionTableFile : public BaseFile
{
    Q_OBJECT
public:
    explicit InspectionTableFile(QObject *parent = 0);

    virtual bool save(const QString &fileName);
};

#endif // __INSPECTION_TABLE_FILE_H__
