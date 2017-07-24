/**
 * @file ut_advanced_menu.h
 * @brief Ut Advanced Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "ut_advanced_menu.h"
#include "ui_base_menu.h"

#include <QDebug>

namespace DplUtSettingMenu {

UtAdvancedMenu::UtAdvancedMenu(QWidget *parent) :
    BaseMenu(parent),
    m_eightPercentItem(new LabelMenuItem(this, tr("Set 80%"))),
    m_dbRefItem(new ComboMenuItem(this, tr("dB Ref."))),
    m_pointQtyItem(new ComboMenuItem(this, tr("Point Qty."))),
    m_scaleFactorItem(new LabelMenuItem(this, tr("Scale Factor"))),
    m_sumGainItem(new SpinMenuItem(this, tr("Sum Gain"), tr("dB")))
{
    ui->layout0->addWidget(m_eightPercentItem);
    ui->layout1->addWidget(m_dbRefItem);
    ui->layout2->addWidget(m_pointQtyItem);
    ui->layout3->addWidget(m_scaleFactorItem);
    ui->layout4->addWidget(m_sumGainItem);

    DplDevice::Device *device = DplDevice::Device::instance();

    connect(device, SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(update(DplDevice::GroupPointer)));

    m_sample = DplDevice::Device::instance()->current_group()->sample();


    QStringList pointQtyList;

    pointQtyList.append(tr("Auto"));
    pointQtyList.append(tr("160"));
    pointQtyList.append(tr("320"));
    pointQtyList.append(tr("640"));
    pointQtyList.append(tr("UserDef"));

    m_dbRefItem->set(s_onOff);

    m_pointQtyItem->set(pointQtyList);

    connect(static_cast<DplUt::Sample *>(m_sample.data()),
            SIGNAL(scale_factor_changed(int)),
            this,
            SLOT(update_scale_factor_item()));

    m_sumGainItem->set(0, 100, 1);
}

UtAdvancedMenu::~UtAdvancedMenu()
{
}

void UtAdvancedMenu::update(const DplDevice::GroupPointer &group)
{
    /* disconnect */
    disconnect(static_cast<DplUt::Sample *>(m_sample.data()),
               SIGNAL(scale_factor_changed(int)),
               this,
               SLOT(update_scale_factor_item()));

    m_sample = group->sample();

    connect(static_cast<DplUt::Sample *>(m_sample.data()),
            SIGNAL(scale_factor_changed(int)),
            this, SLOT(update_scale_factor_item()));

    update_scale_factor_item();
}

void UtAdvancedMenu::update_scale_factor_item()
{
    m_scaleFactorItem->set_text(QString::number(m_sample->scale_factor()));
}

}
