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
    qDebug() <<  "[BaseMenu::eventFilter] "
              <<  "event type " << event->type()
               << " object name " << object->objectName();

    if(QWidget::focusWidget()) {
        qDebug() <<  "[BaseMenu::eventFilter] focus widget = " << QWidget::focusWidget()->objectName();
    }

    if(event->type() == QEvent::FocusOut) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
        if(keyEvent->key() == Qt::Key_Escape) {
            qDebug() << "[QEvent::FocusOut] key Key_Escape. ";
            set_focus_out();
        }
    } else if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
        if(keyEvent->key() == Qt::Key_Up) {
            qDebug() << "[QEvent::KeyPress] key up. ";
            if(!m_menuItemVect.at(m_currentItem)->is_editing()) {
                set_previous_item();
            }
        } else if(keyEvent->key() == Qt::Key_Down) {
            qDebug() << "[QEvent::KeyPress] key down. ";
            if(!m_menuItemVect.at(m_currentItem)->is_editing()) {
                set_next_item();
            }
        } else if(keyEvent->key() == Qt::Key_Return) {
            qDebug() << "[QEvent::KeyPress] key Key_Return. ";
            qDebug() << "[QEvent::KeyPress] key Key_Return.  editing  = " << m_menuItemVect.at(m_currentItem)->is_editing();
            if(m_menuItemVect.at(m_currentItem)->is_editing()) {
                m_menuItemVect.at(m_currentItem)->setFocus();
                m_menuItemVect.at(m_currentItem)->set_selected(true);
                return true;
            }
        }
    } else if(event->type() == QEvent::KeyRelease){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*> (event);
        if(keyEvent->key() == Qt::Key_Escape) {
            qDebug() << "[QEvent::KeyRelease] key Key_Escape. ";
            set_focus_out();
        } else if(keyEvent->key() == Qt::Key_Return) {
            qDebug() << "[QEvent::KeyRelease] key Key_Return. ";
            qDebug() << "[QEvent::KeyRelease] key Key_Return.  editing  = " << m_menuItemVect.at(m_currentItem)->is_editing();
            if(m_menuItemVect.at(m_currentItem)->is_editing()) {
                m_menuItemVect.at(m_currentItem)->set_edit(false);
                set_focus();
            } else {
                m_menuItemVect.at(m_currentItem)->set_edit(true);
            }
            return true;
        }
    }

    return QWidget::eventFilter(object, event);
}

void BaseMenu::insert_item_to_list(QVBoxLayout *layout)
{
    QLayoutItem *item = layout->itemAt(0);
    if(item) {
        if(item->widget()) {
          MenuItem *menuItem = static_cast<MenuItem*> (item->widget());
          if(menuItem) {
              m_menuItemVect.append(menuItem);
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


BaseMenu::~BaseMenu()
{
    delete ui;
}

void BaseMenu::set_focus()
{
    if(!m_initItemListFlag) {
        insert_item_to_list(ui->layout0);
        insert_item_to_list(ui->layout1);
        insert_item_to_list(ui->layout2);
        insert_item_to_list(ui->layout3);
        insert_item_to_list(ui->layout4);
        insert_item_to_list(ui->layout5);
        m_initItemListFlag = true;
    }

    m_menuItemVect.at(m_currentItem)->setFocus();
    m_menuItemVect.at(m_currentItem)->installEventFilter(this);
    m_menuItemVect.at(m_currentItem)->set_selected(true);

}
