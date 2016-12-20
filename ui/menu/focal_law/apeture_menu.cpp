#include "apeture_menu.h"
#include "spin_menu_item.h"

namespace DplFocalLawMenu {

ApetureMenu::ApetureMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Apeture Menu Item */
    m_apetureItem = new SpinMenuItem();
    m_apetureItem->set(tr("Apeture"), "", 0, 64, 0);

    /* First Element menu item */
    m_firstElementItem = new SpinMenuItem;
    m_firstElementItem->set(tr("First Element"), "", 1, 64, 0);

    /* Last Element menu item */
    m_lastElementItem = new SpinMenuItem;
    m_lastElementItem->set(tr("Last Element"), "", 1, 64, 0);

    /* Element Step Menu Item */
    m_elementStep = new SpinMenuItem;
    m_elementStep->set(tr("Element Step"), "", 1, 32, 0);
}

ApetureMenu::~ApetureMenu()
{
    delete m_apetureItem;
    delete m_firstElementItem;
    delete m_lastElementItem;
    delete m_elementStep;
}

void ApetureMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_apetureItem);
    ui->menuItem1->layout()->addWidget(m_firstElementItem);
    ui->menuItem2->layout()->addWidget(m_lastElementItem);
    ui->menuItem3->layout()->addWidget(m_elementStep);
    m_apetureItem->show();
    m_firstElementItem->show();
    m_lastElementItem->show();
    m_elementStep->show();
}

void ApetureMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_apetureItem);
    ui->menuItem1->layout()->removeWidget(m_firstElementItem);
    ui->menuItem2->layout()->removeWidget(m_lastElementItem);
    ui->menuItem3->layout()->removeWidget(m_elementStep);
    m_apetureItem->hide();
    m_firstElementItem->hide();
    m_lastElementItem->hide();
    m_elementStep->hide();
}

}
