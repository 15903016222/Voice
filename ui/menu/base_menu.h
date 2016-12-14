#ifndef __BASE_MENU_H__
#define __BASE_MENU_H__

#include <QObject>

class BaseMenu : public QObject
{
    Q_OBJECT
public:
    explicit BaseMenu(QObject *parent = 0);
    virtual void show() = 0;
    virtual void hide() = 0;

signals:

public slots:

public:
    static QList<double> s_steps1;
    static QList<double> s_steps2;

};

#endif // __BASE_MENU_H__
