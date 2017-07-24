#include "start_menu.h"
#include "ui_base_menu.h"

namespace DplScanMenu {

StartMenu::StartMenu(QWidget *parent) :
    BaseMenu(parent),
    m_startItem(new LabelMenuItem(this, tr("Start"))),
    m_pauseItem(new LabelMenuItem(this, tr("Pause")))
{
    ui->layout0->addWidget(m_startItem);
    ui->layout1->addWidget(m_pauseItem);
}

StartMenu::~StartMenu()
{
}

}
