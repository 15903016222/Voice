#ifndef __INSPECTION_DATA_FILE_H__
#define __INSPECTION_DATA_FILE_H__

#include "base_file.h"

class InspectionDataFile : public BaseFile
{
    Q_OBJECT
public:
    explicit InspectionDataFile(QObject *parent = 0);

    virtual bool save(const QString &fileName);
};

#endif // __INSPECTION_DATA_FILE_H__
