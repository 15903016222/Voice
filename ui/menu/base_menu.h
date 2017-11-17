/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#ifndef __BASE_MENU_H__
#define __BASE_MENU_H__

#include "menu_item/spin_menu_item.h"
#include "menu_item/combo_menu_item.h"
#include "menu_item/label_menu_item.h"

#include <QVector>

namespace Ui {
class BaseMenu;
}

class QVBoxLayout;

class BaseMenu : public QWidget
{
    Q_OBJECT
public:
    explicit BaseMenu(QWidget *parent = 0);
    virtual ~BaseMenu();

    /**
     * @brief set_focus 设置子菜单获取焦点
     */
    void set_focus();

protected:
    bool eventFilter(QObject *object, QEvent *event);

protected:
    static QStringList s_onOff;
    Ui::BaseMenu *ui;

    bool    m_initItemListFlag;
    QVector<MenuItem *> m_menuItemVect;
    int     m_currentItem;

    void insert_item_to_list(QVBoxLayout *layout);
    void set_focus_out();
    void set_previous_item();
    void set_next_item();
};


#endif // __BASE_MENU_H__
