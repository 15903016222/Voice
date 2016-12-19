/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "base_menu.h"

#include "spin_menu_item.h"
#include "combo_menu_item.h"
#include "label_menu_item.h"

QStringList BaseMenu::s_onOff;

BaseMenu::BaseMenu(Ui::SubMenu *ui, const MenuItem::Type types[], QObject *parent)
    :QObject(parent)
{
    this->ui = ui;

    if (s_onOff.isEmpty()) {
        s_onOff.append(tr("On"));
        s_onOff.append(tr("Off"));
    }

    for (int i = 0; i < MAX_ITEMS; ++i) {
        switch(types[i]) {
        case MenuItem::Spin:
            m_menuItem[i] = new SpinMenuItem();
            break;
        case MenuItem::Combo:
            m_menuItem[i] = new ComboMenuItem();
            break;
        default:
            m_menuItem[i] = new LabelMenuItem();
            break;
        }
    }
}

BaseMenu::~BaseMenu()
{
    delete m_menuItem[0];
    delete m_menuItem[1];
    delete m_menuItem[2];
    delete m_menuItem[3];
    delete m_menuItem[4];
    delete m_menuItem[5];
}

void BaseMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_menuItem[0]);
    ui->menuItem1->layout()->addWidget(m_menuItem[1]);
    ui->menuItem2->layout()->addWidget(m_menuItem[2]);
    ui->menuItem3->layout()->addWidget(m_menuItem[3]);
    ui->menuItem4->layout()->addWidget(m_menuItem[4]);
    ui->menuItem5->layout()->addWidget(m_menuItem[5]);

    m_menuItem[0]->show();
    m_menuItem[1]->show();
    m_menuItem[2]->show();
    m_menuItem[3]->show();
    m_menuItem[4]->show();
    m_menuItem[5]->show();
}

void BaseMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_menuItem[0]);
    ui->menuItem1->layout()->removeWidget(m_menuItem[1]);
    ui->menuItem2->layout()->removeWidget(m_menuItem[2]);
    ui->menuItem3->layout()->removeWidget(m_menuItem[3]);
    ui->menuItem4->layout()->removeWidget(m_menuItem[4]);
    ui->menuItem5->layout()->removeWidget(m_menuItem[5]);

    m_menuItem[0]->hide();
    m_menuItem[1]->hide();
    m_menuItem[2]->hide();
    m_menuItem[3]->hide();
    m_menuItem[4]->hide();
    m_menuItem[5]->hide();
}
