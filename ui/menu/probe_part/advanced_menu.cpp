#include "advanced_menu.h"
#include "ui_base_menu.h"

namespace DplProbeMenu {

AdvancedMenu::AdvancedMenu(QWidget *parent) :
    BaseMenu(parent),
    m_loadPartItem(new LabelMenuItem(this, tr("Load Part"))),
    m_clearPartItem(new LabelMenuItem(this, tr("Clear Part")))
{
    ui->layout0->addWidget(m_loadPartItem);
    ui->layout1->addWidget(m_clearPartItem);
}

AdvancedMenu::~AdvancedMenu()
{
}

}
