#include "advanced_menu.h"


namespace DplProbeMenu {

AdvancedMenu::AdvancedMenu(QWidget *parent) :
    BaseMenu(parent),
    m_loadPartItem(new LabelMenuItem(this, tr("Load Part"))),
    m_clearPartItem(new LabelMenuItem(this, tr("Clear Part")))
{
    m_layout0->addWidget(m_loadPartItem);
    m_layout1->addWidget(m_clearPartItem);
}

AdvancedMenu::~AdvancedMenu()
{
}

}
