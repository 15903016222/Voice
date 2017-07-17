#include "area_menu.h"
#include "spin_menu_item.h"

namespace DplScanMenu {

AreaMenu::AreaMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Scan Start Menu Item */
    m_scanStartItem.set(tr("Scan Start"), "mm", 0, 10000, 2);

    /* Scan End menu item */
    m_scanEndItem.set(tr("Scan End"), "mm", 0, 10000, 2);

    /* Scan Resolution menu item */
    m_scanResolutionItem.set(tr("Scan Resolution"), "mm", 0, 100, 2);

    /* Index Start Menu Item */
    m_indexStartItem.set( tr("Index Start"), "mm", 0, 10000, 2);

    /* Index End Menu Item */
    m_indexEndItem.set(tr("Index End"), "mm", 0, 10000, 2);

    /* Index Resolution Menu Item */
    m_indexResolutionItem.set(tr("Index Resolution"), "mm", 0, 100, 2);
}

AreaMenu::~AreaMenu()
{
}

void AreaMenu::show()
{
    ui->layout0->addWidget(&m_scanStartItem);
    ui->layout1->addWidget(&m_scanEndItem);
    ui->layout2->addWidget(&m_scanResolutionItem);
    ui->layout3->addWidget(&m_indexStartItem);
    ui->layout4->addWidget(&m_indexEndItem);
    ui->layout5->addWidget(&m_indexResolutionItem);
    m_scanStartItem.show();
    m_scanEndItem.show();
    m_scanResolutionItem.show();
    m_indexStartItem.show();
    m_indexEndItem.show();
    m_indexResolutionItem.show();
}

void AreaMenu::hide()
{
    ui->layout0->removeWidget(&m_scanStartItem);
    ui->layout1->removeWidget(&m_scanEndItem);
    ui->layout2->removeWidget(&m_scanResolutionItem);
    ui->layout3->removeWidget(&m_indexStartItem);
    ui->layout4->removeWidget(&m_indexEndItem);
    ui->layout5->removeWidget(&m_indexResolutionItem);
    m_scanStartItem.hide();
    m_scanEndItem.hide();
    m_scanResolutionItem.hide();
    m_indexStartItem.hide();
    m_indexEndItem.hide();
    m_indexResolutionItem.hide();
}

}
