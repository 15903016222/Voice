/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#ifndef __BASE_MENU_H__
#define __BASE_MENU_H__

#include <QStringList>

#include "ui_base_menu.h"
#include "spin_menu_item.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"

class BaseMenu : public QObject
{
    Q_OBJECT
public:
    explicit BaseMenu(Ui::BaseMenu *ui, QObject *parent = 0);
    virtual ~BaseMenu();

    bool is_hidden() const;

    /**
     * @brief show  显示接口
     */
    virtual void show() = 0;

    /**
     * @brief hide 隐藏接口
     */
    virtual void hide() = 0;

    /**
     * @brief update    更新接口
     */
//    virtual void update();

protected:
    static QStringList s_onOff;
    bool m_isHidden;
    bool m_updated;
    Ui::BaseMenu *ui;

    void hide_item(QLayout *layout);
};

//void BaseMenu::show()
//{
//    if (m_updated) {
//        update();
//    }
//}

//inline void BaseMenu::hide()
//{

////    MenuItem *item = ui->layout0->findChild<MenuItem *>();
////    if (item) {
////        ui->layout0->removeItem(item);
////        item->hide();
////    }

//    m_isHidden = true;
//}

//inline void BaseMenu::update()
//{
//    m_updated = true;
//    if (is_hidden()) {
//        return;
//    }
//    m_updated = false;
//}

//void BaseMenu::hide_item(QLayout *layout)
//{
////    MenuItem *item = layout->findChild<MenuItem *>();

//}

#endif // __BASE_MENU_H__
