#include "apeture_menu.h"

#include "apeture/apeture_menu_item.h"

namespace DplFocalLawMenu {

ApetureMenu::ApetureMenu(QWidget *parent) :
    BaseMenu(parent),
    m_apetureItem(new ApetureMenuItem(this)),
    m_firstElementItem(new SpinMenuItem(this, tr("First Element"))),
    m_lastElementItem(new SpinMenuItem(this, tr("Last Element"))),
    m_elementStep(new SpinMenuItem(this, tr("Element Step")))
{
    m_layout0->addWidget(m_apetureItem);
    m_layout1->addWidget(m_firstElementItem);
    m_layout2->addWidget(m_lastElementItem);
    m_layout3->addWidget(m_elementStep);

    /* First Element menu item */
    m_firstElementItem->set_decimals(0);

    /* Last Element menu item */
    m_lastElementItem->set_decimals(0);

    /* Element Step Menu Item */
    m_elementStep->set_decimals(0);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

ApetureMenu::~ApetureMenu()
{
}

void ApetureMenu::update_firstElementItem(const DplFocallaw::ScanCnfPointer &scanCnf)
{
    m_firstElementItem->show();
    m_firstElementItem->set_range(1, scanCnf->element_qty());
    m_firstElementItem->set_value(scanCnf->first_element()+1);
}

void ApetureMenu::update_lastElementItem(const DplFocallaw::LinearScanCnfPointer &scanCnf)
{
    m_lastElementItem->show();
    m_lastElementItem->set_range(1, scanCnf->element_qty());
    m_lastElementItem->set_value(scanCnf->last_element()+1);
}

void ApetureMenu::update_elementStep(const DplFocallaw::LinearScanCnfPointer &scanCnf)
{
    m_elementStep->show();
    m_elementStep->set_value(scanCnf->element_step());
}

void ApetureMenu::update(const DplDevice::GroupPointer &group)
{
    m_focallawer = group->focallawer();

    m_firstElementItem->hide();
    m_lastElementItem->hide();
    m_elementStep->hide();

    DplFocallaw::ScanCnfPointer scanCnf = m_focallawer->probe().staticCast<DplFocallaw::PaProbe>()->scan_configure();
    update_firstElementItem(scanCnf);

    if (scanCnf->mode() == DplFocallaw::ScanCnf::Linear) {
        update_lastElementItem(scanCnf.staticCast<DplFocallaw::LinearScanCnf>());
        update_elementStep(scanCnf.staticCast<DplFocallaw::LinearScanCnf>());
    }
}

}
