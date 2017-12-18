#ifndef __SCREEN_FILE_H__
#define __SCREEN_FILE_H__

#include "base_file.h"

class ScreenFile : public BaseFile
{
    Q_OBJECT
public:
    explicit ScreenFile(QObject *parent = 0);

    virtual bool save(const QString &fileName);
};

#endif // __SCREEN_FILE_H__
