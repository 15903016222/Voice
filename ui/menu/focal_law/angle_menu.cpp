#include "angle_menu.h"
#include "ui_base_menu.h"

#include <global.h>

namespace DplFocalLawMenu {

AngleMenu::AngleMenu(QWidget *parent) :
    BaseMenu(parent),
    m_minAngleItem(new SpinMenuItem(this, tr("Min"), DEGREE_STR)),
    m_maxAngleItem(new SpinMenuItem(this, tr("Max"), DEGREE_STR)),
    m_angleStepItem(new SpinMenuItem(this, tr("Step"),DEGREE_STR))
{
    ui->layout0->addWidget(m_minAngleItem);
    ui->layout1->addWidget(m_maxAngleItem);
    ui->layout2->addWidget(m_angleStepItem);

    /* Min.Angle Menu Item */
    m_minAngleItem->set(-89, 89, 0);
    connect(m_minAngleItem, SIGNAL(value_changed(double)),
            this, SLOT(do_minAngleItem_changed(double)));

    /* Max.Angle Menu Item */
    m_maxAngleItem->set(-89, 89, 0);

    /* Angle Step Menu Item */
    m_angleStepItem->set(1, 10, 0);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));
    update(DplDevice::Device::instance()->current_group());
}

AngleMenu::~AngleMenu()
{
}

void AngleMenu::update_minAngleItem(const DplFocallaw::ScanCnfPointer &scanCnf)
{
    m_minAngleItem->show();
    if (scanCnf->mode() == DplFocallaw::ScanCnf::Linear) {
        m_minAngleItem->set_value(scanCnf.staticCast<DplFocallaw::LinearScanCnf>()->angle());
    } else if (scanCnf->mode() == DplFocallaw::ScanCnf::Sectorial) {
        m_minAngleItem->set_value(scanCnf.staticCast<DplFocallaw::SectorialScanCnf>()->first_angle());
    }
}

void AngleMenu::update_maxAngleItem(const DplFocallaw::SectorialScanCnfPointer &scanCnf)
{
    m_maxAngleItem->show();
    m_maxAngleItem->set_value(scanCnf->last_angle());
}

void AngleMenu::update_angleStepItem(const DplFocallaw::SectorialScanCnfPointer &scanCnf)
{
    m_angleStepItem->show();
    m_angleStepItem->set_value(scanCnf->angle_step());
}

void AngleMenu::update(const DplDevice::GroupPointer &group)
{
    m_group = group;
    DplFocallaw::FocallawerPointer focallawer = group->focallawer();
    DplFocallaw::PaProbePointer probe = focallawer->probe().staticCast<DplFocallaw::PaProbe>();

    m_minAngleItem->hide();
    m_maxAngleItem->hide();
    m_angleStepItem->hide();

    DplFocallaw::ScanCnfPointer scanCnf = probe->scan_configure();
    update_minAngleItem(scanCnf);
    if (scanCnf->mode() == DplFocallaw::ScanCnf::Linear) {

    } else if (scanCnf->mode() == DplFocallaw::ScanCnf::Sectorial) {

    }
}

void AngleMenu::do_minAngleItem_changed(double val)
{

}

}
