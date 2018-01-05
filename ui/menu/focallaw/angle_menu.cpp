#include "angle_menu.h"

#include <global.h>

#include <QEvent>

namespace DplFocalLawMenu {

AngleMenu::AngleMenu(QWidget *parent) :
    BaseMenu(parent),
    m_minAngleItem(new SpinMenuItem(this, tr("Min"), DEGREE_STR)),
    m_maxAngleItem(new SpinMenuItem(this, tr("Max"), DEGREE_STR)),
    m_angleStepItem(new SpinMenuItem(this, tr("Step"),DEGREE_STR))
{
    m_layout0->addWidget(m_minAngleItem);
    m_layout1->addWidget(m_maxAngleItem);
    m_layout2->addWidget(m_angleStepItem);

    /* Min.Angle Menu Item */
    m_minAngleItem->set(-89, 89, 0);
    connect(m_minAngleItem, SIGNAL(value_changed(double)),
            this, SLOT(do_minAngleItem_changed(double)));

    /* Max.Angle Menu Item */
    m_maxAngleItem->set(-89, 89, 0);
    connect(m_maxAngleItem, SIGNAL(value_changed(double)),
            this, SLOT(do_maxAngleItem_changed(double)));

    /* Angle Step Menu Item */
    m_angleStepItem->set(1, 10, 0);
    connect(m_angleStepItem, SIGNAL(value_changed(double)),
            this, SLOT(do_angleStepItem_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));
    do_group_changed(DplDevice::Device::instance()->current_group());
}

void AngleMenu::do_group_changed(const DplDevice::GroupPointer &group)
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

void AngleMenu::do_probe_changed(const DplFocallaw::ProbePointer &probe)
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

void AngleMenu::do_scan_changed(const DplFocallaw::ScanCnfPointer &scan)
{
    if (m_scan) {
        if (m_scan->mode() == DplFocallaw::ScanCnf::Linear) {
            disconnect(static_cast<DplFocallaw::LinearScanCnf *>(m_scan.data()),
                       SIGNAL(angle_changed(float)),
                       this, SLOT(update_minAngleItem()));
        } else if (m_scan->mode() == DplFocallaw::ScanCnf::Sectorial) {
            disconnect(static_cast<DplFocallaw::SectorialScanCnf *>(m_scan.data()),
                       SIGNAL(first_angle_changed(float)),
                       this, SLOT(update_minAngleItem()));
            disconnect(static_cast<DplFocallaw::SectorialScanCnf *>(m_scan.data()),
                       SIGNAL(last_angle_changed(float)),
                       this, SLOT(update_maxAngleItem()));
            disconnect(static_cast<DplFocallaw::SectorialScanCnf *>(m_scan.data()),
                       SIGNAL(angle_step_changed(float)),
                       this, SLOT(update_angleStepItem()));
        }
    }

    m_scan = scan;

    update_minAngleItem();
    update_maxAngleItem();
    update_angleStepItem();

    if (m_scan->mode() == DplFocallaw::ScanCnf::Linear) {
        connect(static_cast<DplFocallaw::LinearScanCnf *>(m_scan.data()),
                SIGNAL(angle_changed(float)),
                this, SLOT(update_minAngleItem()));
    } else if (m_scan->mode() == DplFocallaw::ScanCnf::Sectorial) {
        connect(static_cast<DplFocallaw::SectorialScanCnf *>(m_scan.data()),
                SIGNAL(first_angle_changed(float)),
                this, SLOT(update_minAngleItem()));
        connect(static_cast<DplFocallaw::SectorialScanCnf *>(m_scan.data()),
                SIGNAL(last_angle_changed(float)),
                this, SLOT(update_maxAngleItem()));
        connect(static_cast<DplFocallaw::SectorialScanCnf *>(m_scan.data()),
                SIGNAL(angle_step_changed(float)),
                this, SLOT(update_angleStepItem()));
    }
}

void AngleMenu::update_minAngleItem()
{
    m_minAngleItem->setDisabled(false);
    if (m_scan->mode() == DplFocallaw::ScanCnf::Linear) {
        m_minAngleItem->set_value(m_scan.staticCast<DplFocallaw::LinearScanCnf>()->angle());
    } else if (m_scan->mode() == DplFocallaw::ScanCnf::Sectorial) {
        m_minAngleItem->set_value(m_scan.staticCast<DplFocallaw::SectorialScanCnf>()->first_angle());
    }
}

void AngleMenu::update_maxAngleItem()
{
    if (m_scan->mode() != DplFocallaw::ScanCnf::Sectorial) {
        m_maxAngleItem->hide();
        return;
    }

    m_maxAngleItem->show();
    m_maxAngleItem->set_value(m_scan.staticCast<DplFocallaw::SectorialScanCnf>()->last_angle());
}

void AngleMenu::update_angleStepItem()
{
    if (m_scan->mode() != DplFocallaw::ScanCnf::Sectorial) {
        m_angleStepItem->hide();
        return;
    }
    m_angleStepItem->show();
    m_angleStepItem->set_value(m_scan.staticCast<DplFocallaw::SectorialScanCnf>()->angle_step());
}

void AngleMenu::do_minAngleItem_changed(double val)
{
    if (m_scan->mode() == DplFocallaw::ScanCnf::Linear) {
        DplFocallaw::LinearScanCnfPointer cnf = m_scan.staticCast<DplFocallaw::LinearScanCnf>();
        if (!cnf->set_angle(val)) {
            m_minAngleItem->set_value(cnf->angle());
        }
    } else if (m_scan->mode() == DplFocallaw::ScanCnf::Sectorial) {
        DplFocallaw::SectorialScanCnfPointer cnf = m_scan.staticCast<DplFocallaw::SectorialScanCnf>();
        if (!cnf->set_first_angle(val)) {
            m_minAngleItem->set_value(cnf->first_angle());
        }
    }
}

void AngleMenu::do_maxAngleItem_changed(double val)
{
    DplFocallaw::SectorialScanCnfPointer cnf = m_scan.staticCast<DplFocallaw::SectorialScanCnf>();
    if (!cnf->set_last_angle(val)) {
        m_maxAngleItem->set_value(cnf->last_angle());
    }
}

void AngleMenu::do_angleStepItem_changed(double val)
{
    DplFocallaw::SectorialScanCnfPointer cnf = m_scan.staticCast<DplFocallaw::SectorialScanCnf>();
    if (!cnf->set_angle_step(val)) {
        m_angleStepItem->set_value(cnf->angle_step());
    }
}

void AngleMenu::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        m_minAngleItem->set_title(tr("Min"));
        m_maxAngleItem->set_title(tr("Max"));
        m_angleStepItem->set_title(tr("Step"));
        return;
    }
    BaseMenu::changeEvent(e);
}

}
