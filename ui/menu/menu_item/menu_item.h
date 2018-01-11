/**
 * @file menu_item.h
 * @brief menu item base class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __MENU_ITEM_H__
#define __MENU_ITEM_H__

#include <QWidget>
#include <QEvent>

class MenuItem : public QWidget
{
    Q_OBJECT
public:
    explicit MenuItem(QWidget *parent = 0);

protected:
    void update_layout(QWidget *w1, QWidget *w2);
    void changeEvent(QEvent *e);
    virtual void translate();
};

#endif // __MENU_ITEM_H__
