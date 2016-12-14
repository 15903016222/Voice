#ifndef __BASE_MENU_H__
#define __BASE_MENU_H__

#include <QObject>
#include <QStringList>

#include "ui_sub_menu.h"

class BaseMenu : public QObject
{
    Q_OBJECT
public:
    explicit BaseMenu(Ui::SubMenu *ui, QObject *parent = 0);
    virtual void show() = 0;
    virtual void hide() = 0;

signals:

public slots:

protected:
    static QList<double> s_steps1;
    static QList<double> s_steps2;
    static QStringList s_onOff;

    Ui::SubMenu *ui;
};

#endif // __BASE_MENU_H__
