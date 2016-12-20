#include "area_menu.h"
#include "spin_menu_item.h"

namespace DplScanMenu {

AreaMenu::AreaMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Scan Start Menu Item */
    m_scanStartItem = new SpinMenuItem;
    m_scanStartItem->set(tr("Scan Start"), "mm", 0, 10000, 2);

    /* Scan End menu item */
    m_scanEndItem = new SpinMenuItem;
    m_scanEndItem->set(tr("Scan End"), "mm", 0, 10000, 2);

    /* Scan Resolution menu item */
    m_scanResolutionItem = new SpinMenuItem;
    m_scanResolutionItem->set(tr("Scan Resolution"), "mm", 0, 100, 2);

    /* Index Start Menu Item */
    m_indexStartItem = new SpinMenuItem;
    m_indexStartItem->set( tr("Index Start"), "mm", 0, 10000, 2);

    /* Index End Menu Item */
    m_indexEndItem = new SpinMenuItem;
    m_indexEndItem->set(tr("Index End"), "mm", 0, 10000, 2);

    /* Index Resolution Menu Item */
    m_indexResolutionItem = new SpinMenuItem;
    m_indexResolutionItem->set(tr("Index Resolution"), "mm", 0, 100, 2);
}

AreaMenu::~AreaMenu()
{
    delete m_scanStartItem;
    delete m_scanEndItem;
    delete m_scanResolutionItem;
    delete m_indexStartItem;
    delete m_indexEndItem;
    delete m_indexResolutionItem;
}

void AreaMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_scanStartItem);
    ui->menuItem1->layout()->addWidget(m_scanEndItem);
    ui->menuItem2->layout()->addWidget(m_scanResolutionItem);
    ui->menuItem3->layout()->addWidget(m_indexStartItem);
    ui->menuItem4->layout()->addWidget(m_indexEndItem);
    ui->menuItem5->layout()->addWidget(m_indexResolutionItem);
    m_scanStartItem->show();
    m_scanEndItem->show();
    m_scanResolutionItem->show();
    m_indexStartItem->show();
    m_indexEndItem->show();
    m_indexResolutionItem->show();
}

void AreaMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_scanStartItem);
    ui->menuItem1->layout()->removeWidget(m_scanEndItem);
    ui->menuItem2->layout()->removeWidget(m_scanResolutionItem);
    ui->menuItem3->layout()->removeWidget(m_indexStartItem);
    ui->menuItem4->layout()->removeWidget(m_indexEndItem);
    ui->menuItem5->layout()->removeWidget(m_indexResolutionItem);
    m_scanStartItem->hide();
    m_scanEndItem->hide();
    m_scanResolutionItem->hide();
    m_indexStartItem->hide();
    m_indexEndItem->hide();
    m_indexResolutionItem->hide();
}

}
