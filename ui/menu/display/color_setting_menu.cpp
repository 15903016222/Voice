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
    BaseMenu(ui, parent),
    m_amplitudeItem(new LabelMenuItem(tr("Amplitude"))),
    m_depthItem(new LabelMenuItem(tr("Depth"))),
    m_tofdItem(new LabelMenuItem(tr("TOFD")))
{
    ui->layout0->addWidget(m_amplitudeItem);
    ui->layout1->addWidget(m_depthItem);
    ui->layout2->addWidget(m_tofdItem);
}

ColorSettingMenu::~ColorSettingMenu()
{
    delete m_amplitudeItem;
    delete m_depthItem;
    delete m_tofdItem;
}

void ColorSettingMenu::show()
{
    m_amplitudeItem->show();
    m_depthItem->show();
    m_tofdItem->show();
}

void ColorSettingMenu::hide()
{
    m_amplitudeItem->hide();
    m_depthItem->hide();
    m_tofdItem->hide();
}

}
