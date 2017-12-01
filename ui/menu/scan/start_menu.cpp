#include "start_menu.h"


namespace DplScanMenu {

StartMenu::StartMenu(QWidget *parent) :
    BaseMenu(parent),
    m_startItem(new LabelMenuItem(this, tr("Start"))),
    m_pauseItem(new LabelMenuItem(this, tr("Pause")))
{
    m_layout0->addWidget(m_startItem);
    m_layout1->addWidget(m_pauseItem);
}

StartMenu::~StartMenu()
{
}

}
