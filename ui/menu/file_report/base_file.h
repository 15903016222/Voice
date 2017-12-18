#ifndef __BASE_FILE_H__
#define __BASE_FILE_H__

#include <QString>
#include <QObject>

class BaseFile : public QObject
{
    Q_OBJECT
public:
    BaseFile(QObject *parent = 0);

    virtual bool save(const QString &fileName) = 0;
};

#endif // __BASE_FILE_H__
