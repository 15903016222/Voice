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
#include <mcu/mcu.h>

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

    /**
     * @brief set_focus 通过object设置子菜单获取焦点
     */
    void set_focus(QObject *object);

    /**
     * @brief set_selected_item_focus_in 设置已选择的控件焦点
     * @return      true:设置成功；false：设置失败
     */
    bool set_selected_item_focus_in();

    /**
     * @brief has_editing 是否有item正在编辑
     * @return true：有item正在编辑；false:没有item正在编辑；
     */
    bool has_editing();

    /**
     * @brief set_all_item_no_edit 设置所有item为非编辑状态
     */
    void set_all_item_no_edit();

protected:
    bool eventFilter(QObject *object, QEvent *event);

protected:
    static QStringList s_onOff;
    Ui::BaseMenu *ui;

    bool    m_initItemListFlag;
    QVector<MenuItem *> m_menuItemVect;
    int     m_currentItem;
    QObject *m_selectedItem;

    void insert_item_to_list(QVBoxLayout *layout);
    void set_focus_out();
    void set_previous_item();
    void set_next_item();
    void update_item_vector();

};


#endif // __BASE_MENU_H__
