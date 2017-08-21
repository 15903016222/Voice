#include "angle_menu.h"
#include "ui_base_menu.h"

namespace DplFocalLawMenu {

AngleMenu::AngleMenu(QWidget *parent) :
    BaseMenu(parent),
    m_minAngleItem(new SpinMenuItem(this, tr("Min"), tr("&#176;"))),
    m_maxAngleItem(new SpinMenuItem(this, tr("Max"), tr("&#176;"))),
    m_angleStepItem(new SpinMenuItem(this, tr("Step"),tr("&#176;")))
{
    ui->layout0->addWidget(m_minAngleItem);
    ui->layout1->addWidget(m_maxAngleItem);
    ui->layout2->addWidget(m_angleStepItem);

    /* Min.Angle Menu Item */
    m_minAngleItem->set(-89, 89, 0);

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

    m_minAngleItem->hide();
    m_maxAngleItem->hide();
    m_angleStepItem->hide();

    if (focallawer->probe()->is_pa()) {
        DplFocallaw::ScanCnfPointer scanCnf = focallawer->scan_cnf();
        update_minAngleItem(scanCnf);
        if (scanCnf->mode() == DplFocallaw::ScanCnf::Linear) {

        } else if (scanCnf->mode() == DplFocallaw::ScanCnf::Sectorial) {

        }
    }
}

}
