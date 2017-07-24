#include "area_menu.h"
#include "ui_base_menu.h"

namespace DplScanMenu {

AreaMenu::AreaMenu(QWidget *parent) :
    BaseMenu(parent),
    m_scanStartItem(new SpinMenuItem(this, tr("Scan Start"), tr("mm"))),
    m_scanEndItem(new SpinMenuItem(this, tr("Scan Start"), tr("mm"))),
    m_scanResolutionItem(new SpinMenuItem(this, tr("Scan Start"), tr("mm"))),
    m_indexStartItem(new SpinMenuItem(this, tr("Scan Start"), tr("mm"))),
    m_indexEndItem(new SpinMenuItem(this, tr("Scan Start"), tr("mm"))),
    m_indexResolutionItem(new SpinMenuItem(this, tr("Scan Start"), tr("mm")))
{
    ui->layout0->addWidget(m_scanStartItem);
    ui->layout1->addWidget(m_scanEndItem);
    ui->layout2->addWidget(m_scanResolutionItem);
    ui->layout3->addWidget(m_indexStartItem);
    ui->layout4->addWidget(m_indexEndItem);
    ui->layout5->addWidget(m_indexResolutionItem);

    /* Scan Start Menu Item */
    m_scanStartItem->set(0, 10000, 2);

    /* Scan End menu item */
    m_scanEndItem->set(0, 10000, 2);

    /* Scan Resolution menu item */
    m_scanResolutionItem->set(0, 100, 2);

    /* Index Start Menu Item */
    m_indexStartItem->set(0, 10000, 2);

    /* Index End Menu Item */
    m_indexEndItem->set(0, 10000, 2);

    /* Index Resolution Menu Item */
    m_indexResolutionItem->set(0, 100, 2);
}

AreaMenu::~AreaMenu()
{
}

}
