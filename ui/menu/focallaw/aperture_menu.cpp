#include "aperture_menu.h"

#include <QEvent>

namespace DplFocalLawMenu {

ApertureMenu::ApertureMenu(QWidget *parent) :
    BaseMenu(parent),
    m_apertureItem(new SpinMenuItem(this, tr("Aperture"))),
    m_firstElementItem(new SpinMenuItem(this, tr("First Element"))),
    m_lastElementItem(new SpinMenuItem(this, tr("Last Element"))),
    m_stepmenuItem(new SpinMenuItem(this, tr("Element Step")))
{
    m_layout0->addWidget(m_apertureItem);
    m_layout1->addWidget(m_firstElementItem);
    m_layout2->addWidget(m_lastElementItem);
    m_layout3->addWidget(m_stepmenuItem);

    /* aperture menu item */
    m_apertureItem->set_decimals(0);
    connect(m_apertureItem, SIGNAL(value_changed(double)),
            this, SLOT(do_apertureItem_changed(double)));

    /* First Element menu item */
    m_firstElementItem->set_decimals(0);
    connect(m_firstElementItem, SIGNAL(value_changed(double)),
            this, SLOT(do_firstElementItem_changed(double)));

    /* Last Element menu item */
    m_lastElementItem->set_decimals(0);
    connect(m_lastElementItem, SIGNAL(value_changed(double)),
            this, SLOT(do_lastElementItem_changed(double)));

    /* Element Step Menu Item */
    m_stepmenuItem->set_decimals(0);
    connect(m_stepmenuItem, SIGNAL(value_changed(double)),
            this, SLOT(do_stepItem(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));
    do_group_changed(DplDevice::Device::instance()->current_group());
}

void ApertureMenu::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_focallawer) {
        connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
                SIGNAL(probe_changed(DplFocallaw::ProbePointer)),
                this, SLOT(do_probe_changed(DplDevice::GroupPointer)));
    }

    m_focallawer = group->focallawer();

    do_probe_changed(m_focallawer->probe());

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(probe_changed(DplFocallaw::ProbePointer)),
            this, SLOT(do_probe_changed(DplFocallaw::ProbePointer)));
}

void ApertureMenu::do_probe_changed(const DplFocallaw::ProbePointer &probe)
{
    if (m_probe) {
        disconnect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
                   SIGNAL(scan_configure_changed(DplFocallaw::ScanCnfPointer)),
                   this, SLOT(do_scan_changed(DplFocallaw::ScanCnfPointer)));
    }

    if (!probe->is_pa()) {
        m_probe.clear();
        m_scan.clear();
        return;
    }

    m_probe = probe.staticCast<DplFocallaw::PaProbe>();
    do_scan_changed(m_probe->scan_configure());

    connect(static_cast<DplFocallaw::PaProbe *>(m_probe.data()),
            SIGNAL(scan_configure_changed(DplFocallaw::ScanCnfPointer)),
            this, SLOT(do_scan_changed(DplFocallaw::ScanCnfPointer)));
}

void ApertureMenu::do_scan_changed(const DplFocallaw::ScanCnfPointer &scan)
{
    if (m_scan) {
        disconnect(static_cast<DplFocallaw::ScanCnf *>(m_scan.data()),
                   SIGNAL(aperture_changed(uint)),
                   this, SLOT(update_apertureItem()));
        disconnect(static_cast<DplFocallaw::ScanCnf *>(m_scan.data()),
                   SIGNAL(first_element_changed(uint)),
                   this, SLOT(update_firstElementItem()));
        if (m_scan->mode() == DplFocallaw::ScanCnf::Linear) {
            disconnect(static_cast<DplFocallaw::LinearScanCnf *>(m_scan.data()),
                       SIGNAL(last_element_changed(uint)),
                       this, SLOT(update_lastElementItem()));
            disconnect(static_cast<DplFocallaw::LinearScanCnf *>(m_scan.data()),
                       SIGNAL(element_step_changed(uint)),
                       this, SLOT(update_stepMenuItem()));
        }
    }

    m_scan = scan;

    update_apertureItem();
    update_firstElementItem();
    update_lastElementItem();
    update_stepMenuItem();

    connect(static_cast<DplFocallaw::ScanCnf *>(m_scan.data()),
            SIGNAL(aperture_changed(uint)),
            this, SLOT(update_apertureItem()));
    connect(static_cast<DplFocallaw::ScanCnf *>(m_scan.data()),
            SIGNAL(first_element_changed(uint)),
            this, SLOT(update_firstElementItem()));
    if (m_scan->mode() == DplFocallaw::ScanCnf::Linear) {
        connect(static_cast<DplFocallaw::LinearScanCnf *>(m_scan.data()),
                SIGNAL(last_element_changed(uint)),
                this, SLOT(update_lastElementItem()));
        connect(static_cast<DplFocallaw::LinearScanCnf *>(m_scan.data()),
                SIGNAL(element_step_changed(uint)),
                this, SLOT(update_stepMenuItem()));
    }
}

void ApertureMenu::update_apertureItem()
{
    m_apertureItem->setDisabled(false);
    m_apertureItem->set_range(1, m_scan->element_qty());
    m_apertureItem->set_value(m_scan->aperture());
}

void ApertureMenu::update_firstElementItem()
{
    m_firstElementItem->setDisabled(false);
    m_firstElementItem->set_range(1, m_scan->element_qty());
    m_firstElementItem->set_value(m_scan->first_element()+1);
}

void ApertureMenu::update_lastElementItem()
{
    if (m_scan->mode() == DplFocallaw::ScanCnf::Sectorial) {
        m_lastElementItem->hide();
        return;
    }
    m_lastElementItem->show();
    m_lastElementItem->set_range(1, m_scan->element_qty());
    m_lastElementItem->set_value(m_scan.staticCast<DplFocallaw::LinearScanCnf>()->last_element()+1);
}

void ApertureMenu::update_stepMenuItem()
{
    if (m_scan->mode() == DplFocallaw::ScanCnf::Sectorial) {
        m_stepmenuItem->hide();
        return;
    }

    m_stepmenuItem->show();
    m_stepmenuItem->set_range(1, m_scan->element_qty());
    m_stepmenuItem->set_value(m_scan.staticCast<DplFocallaw::LinearScanCnf>()->element_step());
}

void ApertureMenu::do_apertureItem_changed(double val)
{
    if ( !m_scan->set_aperture(val) ) {
        m_apertureItem->set_value(m_scan->aperture());
    }
}

void ApertureMenu::do_firstElementItem_changed(double val)
{
    if ( !m_scan->set_first_element(val-1) ) {
        m_firstElementItem->set_value(m_scan->first_element() + 1);
    }
}

void ApertureMenu::do_lastElementItem_changed(double val)
{
    DplFocallaw::LinearScanCnfPointer cnf = m_scan.staticCast<DplFocallaw::LinearScanCnf>();
    if ( !cnf->set_last_element(val-1) ) {
        m_lastElementItem->set_value(cnf->last_element() + 1);
    }
}

void ApertureMenu::do_stepItem(double val)
{
    DplFocallaw::LinearScanCnfPointer cnf = m_scan.staticCast<DplFocallaw::LinearScanCnf>();
    if ( !cnf->set_element_step(val) ) {
        m_stepmenuItem->set_value(cnf->element_step());
    }
}

void ApertureMenu::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        m_apertureItem->set_title(tr("Aperture"));
        m_firstElementItem->set_title(tr("First Element"));
        m_lastElementItem->set_title(tr("Last Element"));
        m_stepmenuItem->set_title(tr("Element Step"));
        return;
    }
    BaseMenu::changeEvent(e);
}

}
