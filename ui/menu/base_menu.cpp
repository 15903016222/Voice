/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "base_menu.h"
#include "ui_base_menu.h"
#include <QDebug>
#include <QShowEvent>
#include <QMouseEvent>


QStringList BaseMenu::s_onOff;

BaseMenu::BaseMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseMenu),
    m_initItemListFlag(false),
    m_currentItem(0)
{
    ui->setupUi(this);

    if (s_onOff.isEmpty()) {
        s_onOff.append(tr("On"));
        s_onOff.append(tr("Off"));
    }
    hide();
}


bool BaseMenu::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::FocusOut) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
        if(keyEvent->key() == Qt::Key_Escape) {
            set_focus_out();
        }

        if(object->objectName() == m_menuItemVect.at(m_currentItem)->objectName()) {
            m_menuItemVect.at(m_currentItem)->set_selected(false);
        }

    } else if(event->type() == QEvent::FocusIn) {
        m_menuItemVect.at(m_currentItem)->set_selected(true);
    } else if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);

        if(keyEvent->key() == Qt::Key_Up) {
            if(!m_menuItemVect.at(m_currentItem)->is_editing()) {
                set_previous_item();
            }
        } else if(keyEvent->key() == Qt::Key_Down) {
            if(!m_menuItemVect.at(m_currentItem)->is_editing()) {
                set_next_item();
            }
        } else if(keyEvent->key() == Qt::Key_Return) {
            /* spin_menu_item控件，通过飞梭调节数值 */
            if(m_menuItemVect.at(m_currentItem)->is_editing()) {
                m_menuItemVect.at(m_currentItem)->setFocus();
                m_menuItemVect.at(m_currentItem)->set_selected(true);
                return true;
            }
        } else if(keyEvent->key() == Qt::Key_Escape) {
            m_menuItemVect.at(m_currentItem)->setFocus();
            m_menuItemVect.at(m_currentItem)->set_selected(true);
            return true;
        }
    } else if(event->type() == QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
        if(keyEvent->key() == Qt::Key_Escape) {
            if(!m_menuItemVect.at(m_currentItem)->is_editing()) {
                set_focus_out();
            } else {
                m_menuItemVect.at(m_currentItem)->set_edit(false);
                return true;
            }
        } else if(keyEvent->key() == Qt::Key_Return) {
            if(m_menuItemVect.at(m_currentItem)->is_editing()) {
                m_menuItemVect.at(m_currentItem)->set_edit(false);
                set_focus();
            } else {
                m_menuItemVect.at(m_currentItem)->set_edit(true);
            }
            return true;
        }
    } else if(event->type() == QEvent::Leave) {
        set_focus_out();
    }

    return QWidget::eventFilter(object, event);
}

void BaseMenu::insert_item_to_list(QVBoxLayout *layout)
{
    for(int i = 0; i < layout->count(); ++i) {
        QLayoutItem *item = layout->itemAt(i);
        if(item) {
            if(item->widget()) {
                MenuItem *menuItem = static_cast<MenuItem*> (item->widget());
                if(menuItem && (!menuItem->isHidden())) {
                    m_menuItemVect.append(menuItem);
                }
            }
        }
    }
}

void BaseMenu::set_focus_out()
{
    MenuItem *currentMenuItem = m_menuItemVect.at(m_currentItem);
    currentMenuItem->removeEventFilter(this);
    currentMenuItem->set_selected(false);
    currentMenuItem->setFocusPolicy(Qt::NoFocus);
    m_currentItem = 0;
}

void BaseMenu::set_previous_item()
{
    update_item_vector();

    MenuItem *currentMenuItem = m_menuItemVect.at(m_currentItem);
    currentMenuItem->removeEventFilter(this);
    currentMenuItem->set_selected(false);

    bool wantShow = false;
    for(int i = 0; i < m_menuItemVect.size(); ++i) {
        --m_currentItem;
        if(m_currentItem < 0) {
            m_currentItem = m_menuItemVect.size() - 1;
        }

        if(!m_menuItemVect.at(m_currentItem)->isHidden()) {
            wantShow = true;
            break;
        }
    }

    if(wantShow) {
        set_focus();
    }
}

void BaseMenu::set_next_item()
{
    update_item_vector();

    MenuItem *currentMenuItem = m_menuItemVect.at(m_currentItem);
    currentMenuItem->removeEventFilter(this);
    currentMenuItem->set_selected(false);

    bool wantShow = false;
    for(int i = 0; i < m_menuItemVect.size(); ++i) {
        ++m_currentItem;
        if(m_currentItem >= m_menuItemVect.size()) {
            m_currentItem = 0;
        }

        if(!m_menuItemVect.at(m_currentItem)->isHidden()) {
            wantShow = true;
            break;
        }
    }

    if(wantShow) {
        set_focus();
    }
}

void BaseMenu::update_item_vector()
{
    m_menuItemVect.clear();

    insert_item_to_list(ui->layout0);
    insert_item_to_list(ui->layout1);
    insert_item_to_list(ui->layout2);
    insert_item_to_list(ui->layout3);
    insert_item_to_list(ui->layout4);
    insert_item_to_list(ui->layout5);
}

BaseMenu::~BaseMenu()
{
    delete ui;
}

void BaseMenu::set_focus()
{
    update_item_vector();

    if(m_menuItemVect.size() <= 0) {
       return;
    }

    if(m_currentItem < 0
            || m_menuItemVect.size() <= m_currentItem) {
        m_currentItem = 0;
    }

    if(set_selected_item_focus_in()) {
        return;
    }

    m_menuItemVect.at(m_currentItem)->activateWindow();
    m_menuItemVect.at(m_currentItem)->setFocusPolicy(Qt::WheelFocus);
    m_menuItemVect.at(m_currentItem)->setFocus();
    m_menuItemVect.at(m_currentItem)->installEventFilter(this);
    m_menuItemVect.at(m_currentItem)->set_selected(true);
}

void BaseMenu::set_focus(QObject *object)
{
    if(NULL == object) {
        return;
    }

    update_item_vector();

    for(int i = 0; i < m_menuItemVect.size(); ++i) {
        if((m_menuItemVect.at(i) == object)
                && (!m_menuItemVect.at(i)->isHidden())) {

            m_currentItem = i;
            m_menuItemVect.at(m_currentItem)->activateWindow();
            m_menuItemVect.at(m_currentItem)->setFocusPolicy(Qt::WheelFocus);
            m_menuItemVect.at(m_currentItem)->setFocus();
            m_menuItemVect.at(m_currentItem)->installEventFilter(this);
            m_menuItemVect.at(m_currentItem)->set_selected(true);
        }
    }
}

bool BaseMenu::set_selected_item_focus_in()
{
    update_item_vector();

    for(int i = 0; i < m_menuItemVect.size(); ++i) {

        if((m_menuItemVect.at(i)->is_editing() || m_menuItemVect.at(i)->is_selected())
                && (!m_menuItemVect.at(i)->isHidden())) {

            m_currentItem = i;
            m_menuItemVect.at(m_currentItem)->activateWindow();
            m_menuItemVect.at(m_currentItem)->setFocusPolicy(Qt::WheelFocus);
            m_menuItemVect.at(m_currentItem)->setFocus();
            m_menuItemVect.at(m_currentItem)->installEventFilter(this);
            m_menuItemVect.at(m_currentItem)->set_selected(true);
            m_menuItemVect.at(m_currentItem)->set_edit(false);
            return true;
        }
    }

    return false;
}

bool BaseMenu::has_editing()
{
    update_item_vector();

    for(int i = 0; i < m_menuItemVect.size(); ++i) {
        if(m_menuItemVect.at(i)->is_editing()) {
            return true;
        }
    }
    return false;
}

void BaseMenu::set_all_item_no_edit()
{
    update_item_vector();
    for(int i = 0; i < m_menuItemVect.size(); ++i) {
        m_menuItemVect.at(i)->set_edit(false);
    }
}

