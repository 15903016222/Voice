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
#include <QString>

class MenuItem : public QWidget
{
    Q_OBJECT
public:
    explicit MenuItem(QWidget *parent = 0);
    virtual void set_selected(bool flag) = 0;
    virtual void set_edit(bool flag) = 0;
    inline  bool is_editing() { return m_isEditing; }

protected:
    QString m_title;
    bool    m_isEditing;
};

#endif // __MENU_ITEM_H__
