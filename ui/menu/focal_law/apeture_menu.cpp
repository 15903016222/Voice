#include "apeture_menu.h"
#include "ui_base_menu.h"

namespace DplFocalLawMenu {

ApetureMenu::ApetureMenu(QWidget *parent) :
    BaseMenu(parent),
    m_apetureItem(new SpinMenuItem(this, tr("Apeture"))),
    m_firstElementItem(new SpinMenuItem(this, tr("First Element"))),
    m_lastElementItem(new SpinMenuItem(this, tr("Last Element"))),
    m_elementStep(new SpinMenuItem(this, tr("Element Step")))
{
    ui->layout0->addWidget(m_apetureItem);
    ui->layout1->addWidget(m_firstElementItem);
    ui->layout2->addWidget(m_lastElementItem);
    ui->layout3->addWidget(m_elementStep);

    /* Apeture Menu Item */
    m_apetureItem->set(0, 64, 0);

    /* First Element menu item */
    m_firstElementItem->set(1, 64, 0);

    /* Last Element menu item */
    m_lastElementItem->set(1, 64, 0);

    /* Element Step Menu Item */
    m_elementStep->set(1, 32, 0);
}

ApetureMenu::~ApetureMenu()
{
}

}
