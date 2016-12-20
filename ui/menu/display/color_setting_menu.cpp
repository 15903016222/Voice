/**
 * @file color_setting_menu.cpp
 * @brief Color Setting menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "color_setting_menu.h"
#include "label_menu_item.h"

namespace DplDisplayMenu {

ColorSettingMenu::ColorSettingMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Amplitude menu item */
    m_amplitudeItem = new LabelMenuItem;
    m_amplitudeItem->set(tr("Amplitude"), "");

    /* Depth menu item */
    m_depthItem = new LabelMenuItem;
    m_depthItem->set(tr("Depth"), "");

    /* TOFD menu item */
    m_tofdItem = new LabelMenuItem;
    m_tofdItem->set(tr("TOFD"), "");
}

ColorSettingMenu::~ColorSettingMenu()
{
    delete m_amplitudeItem;
    delete m_depthItem;
    delete m_tofdItem;
}

void ColorSettingMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_amplitudeItem);
    ui->menuItem1->layout()->addWidget(m_depthItem);
    ui->menuItem2->layout()->addWidget(m_tofdItem);
    m_amplitudeItem->show();
    m_depthItem->show();
    m_tofdItem->show();
}

void ColorSettingMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_amplitudeItem);
    ui->menuItem1->layout()->removeWidget(m_depthItem);
    ui->menuItem2->layout()->removeWidget(m_tofdItem);
    m_amplitudeItem->hide();
    m_depthItem->hide();
    m_tofdItem->hide();
}

}
