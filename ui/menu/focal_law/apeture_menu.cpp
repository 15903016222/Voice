#include "apeture_menu.h"
#include "spin_menu_item.h"

namespace DplFocalLawMenu {

ApetureMenu::ApetureMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Apeture Menu Item */
    m_apetureItem.set(tr("Apeture"), "", 0, 64, 0);

    /* First Element menu item */
    m_firstElementItem.set(tr("First Element"), "", 1, 64, 0);

    /* Last Element menu item */
    m_lastElementItem.set(tr("Last Element"), "", 1, 64, 0);

    /* Element Step Menu Item */
    m_elementStep.set(tr("Element Step"), "", 1, 32, 0);
}

ApetureMenu::~ApetureMenu()
{
}

void ApetureMenu::show()
{
    ui->layout0->addWidget(&m_apetureItem);
    ui->layout1->addWidget(&m_firstElementItem);
    ui->layout2->addWidget(&m_lastElementItem);
    ui->layout3->addWidget(&m_elementStep);
    m_apetureItem.show();
    m_firstElementItem.show();
    m_lastElementItem.show();
    m_elementStep.show();
}

void ApetureMenu::hide()
{
    ui->layout0->removeWidget(&m_apetureItem);
    ui->layout1->removeWidget(&m_firstElementItem);
    ui->layout2->removeWidget(&m_lastElementItem);
    ui->layout3->removeWidget(&m_elementStep);
    m_apetureItem.hide();
    m_firstElementItem.hide();
    m_lastElementItem.hide();
    m_elementStep.hide();
}

}
