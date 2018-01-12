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

#include <QWidget>
#include <QLayout>
#include <QEvent>

class QVBoxLayout;

class BaseMenu : public QWidget
{
    Q_OBJECT
public:
    explicit BaseMenu(QWidget *parent = 0);

protected:
    static QStringList s_onOff;

    QVBoxLayout *create_layout();

    QVBoxLayout *m_layout0;
    QVBoxLayout *m_layout1;
    QVBoxLayout *m_layout2;
    QVBoxLayout *m_layout3;
    QVBoxLayout *m_layout4;
    QVBoxLayout *m_layout5;
    QVBoxLayout *m_layout6;
};


#endif // __BASE_MENU_H__
