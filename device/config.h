#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <QObject>

namespace DplDevice {

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = 0) : QObject(parent) {}

signals:

public slots:

protected:

private:
};

}
#endif // __CONFIG_H__
